{ stdenv
, buildPythonPackage ? null
, boost17x
, cmakeMinimal
, mdot
, nix-gitignore
, ninja
, numpy ? null
, pybind11 ? null
, pytest ? null
, src ? nix-gitignore.gitignoreSourcePure [ ".gitignore" "buil*" ] ./.
, version ? "0.0.1"
}:
let

in
#{

  # libfhmdot = stdenv.mkDerivation {
  #   name = "libfhmdot";
  #   inherit src version;

  #   nativeBuildInputs = [ cmakeMinimal ninja ];
  #   buildInputs = [ boost17x tbb ];

  #   cmakeFlags = [
  #     "-DCMAKE_BUILD_TYPE=Release"
  #     "-DPROJECT_TESTS=On"
  #     "-DPROJECT_SANDBOX=OFF"
  #     "-DPROJECT_PYTHON=OFF"
  #   ];
  #   ninjaFlags = [ "-v" ];
  #   makeFlags = [ "VERBOSE=1" ];

  #   enableParallelBuilding = true;
  #   enableParallelChecking = true;

  #   installPhase = "ninja install";
  # };

  #  pyfhmdot =

buildPythonPackage {
  name = "pyfhmdot-${version}";
  inherit version;
  inherit src;

  format = "other";

  nativeBuildInputs = [ cmakeMinimal ninja ];
  buildInputs = [ boost17x mdot pybind11 ];
  propagatedBuildInputs = [ numpy ];
  checkInputs = [ pytest ];

  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=Release"
    "-DPROJECT_TESTS=ON"
    "-DPROJECT_SANDBOX=OFF"
    "-DPROJECT_PRECISION_FLOAT32=OFF"
    "-DPROJECT_PYTHON=ON"
  ];
  ninjaFlags = [ "-v" ];
  makeFlags = [ "VERBOSE=1" ];

  enableParallelBuilding = true;
  enableParallelChecking = true;

  installPhase = "ninja install";

  postInstall = ''
    # export PYTHONPATH=$out/lib/python3.9/site-packages:$$PYTHONPATH
  '';
}
#}
