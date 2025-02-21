{ pkgs ? import
    (
      builtins.fetchTarball {
        url = "https://github.com/NixOS/nixpkgs/archive/e387bb3a4d0d63446086abbfbe2117e80fe3522a.tar.gz";
        sha256 = "sha256:1hhla9k5v0ri76vcaz7pmkwc7kqj45hca3ygfd1c1lsbg01fnvbp";
      }
    )
    {
      config.allowUnfree = true;
    }
, clangSupport ? false
}:

with pkgs;
assert hostPlatform.isx86_64;

let

  mkCustomShell = mkShell.override { stdenv = if clangSupport then clangStdenv else gccStdenv; };

  vscodeExt = vscode-with-extensions.override {
    vscodeExtensions = with vscode-extensions; [
      bbenoist.nix
      eamodio.gitlens
      ms-vscode.cpptools
      # ms-python.python
      # ms-python.vscode-pylance
    ] ++ vscode-utils.extensionsFromVscodeMarketplace [
      {
        name = "cmake";
        publisher = "twxs";
        version = "0.0.17";
        sha256 = "CFiva1AO/oHpszbpd7lLtDzbv1Yi55yQOQPP/kCTH4Y=";
      }
      {
        name = "cmake-tools";
        publisher = "ms-vscode";
        version = "1.10.5";
        sha256 = "T57uCK1rGe3dBnYbK7QhN2NG3NwTEZm0/EY8S1Pyf7I=";
      }
      {
        name = "emacs-mcx";
        publisher = "tuttieee";
        version = "0.41.2";
        sha256 = "LCnPyvl0YLPgIaBODwJGQ1Nubx1rhASexIKbuijJq1M=";
      }
    ];
  };

  pythonEnv = python3.withPackages (ps: with ps;
    [ numpy pybind11 pytest ] # ++ [ ipython mypy pylint ]
  );
in
mkCustomShell {
  buildInputs = [ boost lapack spdlog tbb ]; # mkl

  nativeBuildInputs = [ cmake gnumake ninja ] ++ [
    bashCompletion
    bashInteractive
    black
    cacert
    clang-tools
    cmake-format
    cmakeCurses
    # cppcheck
    emacs-nox
    git
    # hyperfine
    less
    # llvm
    # more
    nixpkgs-fmt
    pkg-config
  ] ++ lib.optionals (!clangSupport) [ gdb ] ++ lib.optionals (clangSupport) [ lldb ] ++
    lib.optionals (hostPlatform.isLinux) [ vscodeExt ] ++ [ pythonEnv ];

  shellHook = ''
    mkdir -p $(pwd)/.trash_config/
    export HOME=$(pwd)/.trash_config;
    export SSL_CERT_FILE=${cacert}/etc/ssl/certs/ca-bundle.crt
  '';
}
