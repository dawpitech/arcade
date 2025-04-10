/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ScoreStorage.hpp
*/

#ifndef SCORESTORAGE_HPP
    #define SCORESTORAGE_HPP

    #include <cstring>
    #include <fstream>
    #include <string>

class SaveFile
{
    public:
        class ScoreFileException final : public std::exception
        {
            public:
                explicit ScoreFileException(const std::string& what)
                {
                    this->_what = what;
                }

                [[nodiscard]] const char *what() const noexcept override
                {
                    return this->_what.c_str();
                }

            private:
                std::string _what;
        };

        static void saveScore(const std::string& gameName, const std::string& playername, const int score)
        {
            save_file_t saveFile = {.magic_bytes = MAGIC_BYTES};

            if (std::ifstream file(SCORE_FILENAME.data(), std::ios::in | std::ios::binary); file.is_open()) {
                file.read(reinterpret_cast<char*>(&saveFile), sizeof(saveFile));
                if (saveFile.magic_bytes != MAGIC_BYTES)
                    throw ScoreFileException("Save file corrupted");
                file.close();
                std::cout << "save loaded" << std::endl;
            } else
                createSaveFile();

            bool game_found = false;
            for (auto &[r_game_name, r_username, r_score] : saveFile.game_saves) {
                if (r_game_name == gameName && r_username == playername) {
                    if (r_score == score)
                        return;
                    r_score = score;
                    game_found = true;
                    break;
                }
            }

            if (!game_found) {
                std::cout << "Game not found, creating..." << std::endl;
                for (auto &[r_game_name, r_username, r_score] : saveFile.game_saves) {
                    if (r_game_name[0] == '\0') {
                        std::strncpy(r_game_name, gameName.c_str(), gameName.size());
                        std::strncpy(r_username, playername.c_str(), playername.size());
                        r_game_name[sizeof(r_game_name) - 1] = '\0';
                        r_username[sizeof(r_username) - 1] = '\0';
                        r_score = score;
                        break;
                    }
                }
            }


            std::ofstream outFile(SCORE_FILENAME.data(), std::ios::out | std::ios::binary | std::ios::trunc);
            if (!outFile)
                throw ScoreFileException("Couldn't write save file");

            outFile.write(reinterpret_cast<const char*>(&saveFile), sizeof(saveFile));
            outFile.close();
        }

        static int loadScore(const std::string& gameName, const std::string& playername)
        {
            save_file_t saveFile = {};
            std::ifstream file( SCORE_FILENAME.data(), std::ios::in | std::ios::binary);

            if (!file.is_open())
                return createSaveFile(), 0;

            file.read(reinterpret_cast<char*>(&saveFile), sizeof(saveFile));
            if (saveFile.magic_bytes != MAGIC_BYTES)
                throw ScoreFileException("Save file corrupted");

            for (const auto &[game_name, username, score] : saveFile.game_saves)
                if (game_name == gameName && username == playername)
                    return file.close(), score;

            file.close();
            return 0;
        }

    private:
        static constexpr std::string_view SCORE_FILENAME = "./.arcade_save\0";
        static constexpr unsigned short MAGIC_BYTES = 0xADDE;

        static void createSaveFile()
        {
            save_file_t saveFile = {};
            std::ofstream outFile(SCORE_FILENAME.data(), std::ios::out | std::ios::binary);

            if (!outFile)
                throw ScoreFileException("Couldn't create save file");

            saveFile.magic_bytes = MAGIC_BYTES;
            outFile.write(reinterpret_cast<const char*>(&saveFile), sizeof(saveFile));
            outFile.close();
        }

        typedef struct game_save_s {
            char game_name[64];
            char username[4];
            int score;
        } game_save_t;

        typedef struct save_file_s {
            unsigned short magic_bytes;
            game_save_t game_saves[8];
        } save_file_t;
};

#endif //SCORESTORAGE_HPP
