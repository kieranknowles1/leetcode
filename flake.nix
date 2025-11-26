{
  description = "A flake based on my NixOS configuration";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    systems.url = "github:nix-systems/default-linux";

    flake-parts = {
      url = "github:hercules-ci/flake-parts";
      inputs.nixpkgs-lib.follows = "nixpkgs";
    };

    nixcfg = {
      url = "github:kieranknowles1/nixcfg";
      inputs.nixpkgs.follows = "nixpkgs";
      inputs.flake-parts.follows = "flake-parts";
      inputs.systems.follows = "systems";

      # Disable inputs not needed outside of nixcfg
      # These can be re-enabled if needed
      inputs.copyparty.follows = "";
      inputs.factorio-blueprints.follows = "";
      inputs.firefox-addons.follows = "";
      inputs.flake-utils.follows = "";
      inputs.home-manager.follows = "";
      inputs.ixx.follows = "";
      inputs.nix-index-database.follows = "";
      inputs.nix-minecraft.follows = "";
      inputs.nixos-cosmic.follows = "";
      inputs.nixos-raspberrypi.follows = "";
      inputs.nuschtosSearch.follows = "";
      inputs.sops-nix.follows = "";
      inputs.src-openmw.follows = "";
      inputs.src-tldr.follows = "";
      inputs.stylix.follows = "";
      inputs.vscode-extensions.follows = "";
    };
  };

  outputs = {
    flake-parts,
    nixcfg,
    ...
  } @ inputs:
    flake-parts.lib.mkFlake {inherit inputs;} {
      systems = import inputs.systems;

      imports = [
        nixcfg.flakeModules.treefmt
      ];

      perSystem = {
        pkgs,
        inputs',
        ...
      }: {
        devShells = {
          default = inputs'.nixcfg.devShells.cmake.override {
            name = "leetcode";
            libraries = with pkgs; [
              gtest
            ];
          };
        };
      };
    };
}
