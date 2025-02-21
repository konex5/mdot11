{
  description = "fhmdot - Fast Hilbert Matrix Dot";

  nixConfig.bash-prompt = "\\033[0;33m\\033[1m\[dev-fhmdot\] \\w\\033[0m\\033[0m$ ";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

  outputs = { self, nixpkgs }:
    let
      forCustomSystems = custom: f: nixpkgs.lib.genAttrs custom (system: f system);
      allSystems = [ "x86_64-linux" "i686-linux" "aarch64-linux" "x86_64-darwin" ];
      devSystems = [ "x86_64-linux" "x86_64-darwin" ];
      forAllSystems = forCustomSystems allSystems;
      forDevSystems = forCustomSystems devSystems;

      nixpkgsFor = forAllSystems (system:
        import nixpkgs {
          inherit system;
          config.allowUnfree = true;
          overlays = [ self.overlay ];
        }
      );

      repoName = "fhmdot";
      repoVersion = nixpkgsFor.x86_64-linux.python3Packages.fhmdot.version;
      repoDescription = "fhmdot - Fast Hilbert Matrix <|·|>";
    in
    {
      overlay = final: prev:
        let
          inherit (prev.lib) composeExtensions;
          pythonPackageOverrides = python-self: python-super: {
            fhmdot = python-self.callPackage ./derivation.nix {
              src = self;
              stdenv = if prev.stdenv.hostPlatform.isDarwin then final.clangStdenv else final.gccStdenv;
            };
            fhmdot-clang = python-self.callPackage ./derivation.nix {
              src = self;
              stdenv = final.clangStdenv;
            };
          };
        in
        {
          python37 = prev.python37.override (old: {
            packageOverrides =
              composeExtensions (old.packageOverrides or (_: _: { }))
                pythonPackageOverrides;
          });
          python38 = prev.python38.override (old: {
            packageOverrides =
              composeExtensions (old.packageOverrides or (_: _: { }))
                pythonPackageOverrides;
          });
          python39 = prev.python39.override (old: {
            packageOverrides =
              composeExtensions (old.packageOverrides or (_: _: { }))
                pythonPackageOverrides;
          });
          python3 = final.python39;
        };

      devShell = forDevSystems (system:
        let pkgs = nixpkgsFor.${system}; in pkgs.callPackage ./shell.nix { }
      );

      hydraJobs = {
        build = forDevSystems (system: nixpkgsFor.${system}.python3Packages.fhmdot);
        build-clang = forDevSystems (system: nixpkgsFor.${system}.python3Packages.fhmdot-clang);

        release = forDevSystems (system:
          with nixpkgsFor.${system}; releaseTools.aggregate
            {
              name = "${repoName}-release-${repoVersion}";
              constituents =
                [
                  self.hydraJobs.build.${system}
                  self.hydraJobs.build-clang.${system}
                  #self.hydraJobs.docker.${system}
                ] ++ lib.optionals (hostPlatform.isLinux) [
                  #self.hydraJobs.deb.x86_64-linux
                  #self.hydraJobs.rpm.x86_64-linux
                  #self.hydraJobs.coverage.x86_64-linux
                ];
              meta.description = "hydraJobs: ${repoDescription}";
            });
      };
      packages = forAllSystems (system:
        with nixpkgsFor.${system}; {
          inherit (python3Packages) fhmdot fhmdot-clang;
        });

      defaultPackage = forAllSystems (system:
        self.packages.${system}.fhmdot);

      apps = forAllSystems (system: {
        fhmdot = {
          type = "app";
          program = "${self.packages.${system}.fhmdot}/bin/cli_golden";
        };
        fhmdot-clang = {
          type = "app";
          program = "${self.packages.${system}.fhmdot-clang}/bin/cli_golden";
        };
      }
      );

      defaultApp = forAllSystems (system: self.apps.${system}.fhmdot);

      templates = {
        fhmdot = {
          description = "template - ${repoDescription}";
          path = ./.;
        };
      };

      defaultTemplate = self.templates.fhmdot;
    };
}
