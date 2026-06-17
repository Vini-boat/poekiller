$cppFiles = Get-ChildItem -Path .\src -Filter *.cpp -Recurse

$srcPaths = $cppFiles.FullName
$outputExe = ".\out\main.exe"

$compiler = "g++"
$toolchain = "--gcc-toolchain=C:/msys64/ucrt64/ -target x86_64-w64-mingw32"
$cpp_version = "-std=c++20"
$srcPaths | foreach {write-host $_}
$includePath = ".\include"
$opt_level = "-O3"
$warnings = $("-Wall","-Wextra","-Wpedantic","-Wconversion","-Wsign-conversion")
$raylib_deps = $("-lraylib","-lopengl32","-lgdi32","-lwinmm")


$cmd = "$compiler $cpp_version -o $outputExe $srcPaths -I $includePath $opt_level $warnings $raylib_deps"
$cmd
invoke-expression $cmd

$cmd = "clang-tidy .\src\*.cpp -- $cpp_version $toolchain"
$cmd 
invoke-expression $cmd