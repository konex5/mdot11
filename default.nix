with (import
  (
    builtins.fetchTarball {
      url = "https://github.com/NixOS/nixpkgs/archive/e387bb3a4d0d63446086abbfbe2117e80fe3522a.tar.gz";
      sha256 = "sha256:1hhla9k5v0ri76vcaz7pmkwc7kqj45hca3ygfd1c1lsbg01fnvbp";
    }
  )
  {
    config.allowUnfree = true;
  });

with python3Packages;

let
  stdenv = if stdenv.hostPlatform.isDarwin then clangStdenv else gccStdenv;
in
callPackage ./derivation.nix { }
