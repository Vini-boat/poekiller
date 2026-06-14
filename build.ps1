$cppFiles = Get-ChildItem -Path .\src -Filter *.cpp -Recurse

$srcPaths = $cppFiles.FullName
$outputExe = ".\out\main.exe"

$cpp_version = "-std=c++20"
$srcPaths | foreach {write-host $_}
$includePath = ".\include"
$opt_level = "-O3"
$raylib_deps = $("-lraylib","-lopengl32","-lgdi32","-lwinmm")

$cmd = "g++ $cpp_version -o $outputExe $srcPaths -I $includePath $opt_level $raylib_deps"
$cmd
invoke-expression $cmd