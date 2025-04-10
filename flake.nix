{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.11";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        cc = pkgs.gcc14;

        deps = with pkgs; [
          libcxx
          gnumake
          criterion
        ] ++ [ cc ];
      in
      {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            valgrind
            mold
            cmake
            doxygen
            pkg-config
            sfml
            ncurses
            SDL2
            SDL2_ttf
            SDL2_image
            hexyl
          ] ++ deps;
        };

        formatter = pkgs.nixpkgs-fmt;
      });
}
