{ stdenv
, buildPythonPackage
, src
, boost17x
, cmakeMinimal
, ninja
, numpy
, pybind11
, pytest
, sphinx
, sphinx_rtd_theme
}:
let
  version = "0.0.0";
in {

  fhmdot = stdenv.mkDerivation {
    name = "fhmdot";
    inherit src version;

    nativeBuildInputs = [ cmakeMinimal ninja ];
    buildInputs = [ boost17x pybind11 ];
  
    cmakeFlags = [
      "-DCMAKE_BUILD_TYPE=Release"
      "-DPROJECT_TESTS=On"
      "-DPROJECT_SANDBOX=OFF"
      "-DPROJECT_PYTHON=OFF"
    ];
    ninjaFlags = [ "-v" ];
    makeFlags = [ "VERBOSE=1" ];
  
    enableParallelBuilding = true;
    enableParallelChecking = true;
  
    installPhase = "ninja install";
  };

  pyfhmdot = buildPythonPackage rec {
    pname = "pymdot";
    version = "0.0.0";
    format = "other";
    inherit src;
  
    nativeBuildInputs = [ cmake ninja ];
    buildInputs = [ boost17x pybind11 ];
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
  
    # excludedTests = [ "test_python_interface" ];
    # installCheckPhase = ''
    #   runHook preCheck
    #   ctest -V -E "${builtins.concatStringsSep "|" excludedTests}"
    #   # export PYTHONPATH=$out/bin:$PYTHONPATH
    #   # python -c "import pyview"
    #   # pytest $src/tests/python -p no:cacheprovider
    #   runHook postCheck
    # '';
}
