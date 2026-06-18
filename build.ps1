# compiler
$compiler = "g++"
$outputExe = ".\out\main.exe"

$cppVersion = "-std=c++20"
$optLevel = "-O3"

$warnings = @(
    "-Wall"
    "-Wextra"
    "-Wpedantic"
    "-Wconversion"
    "-Wsign-conversion"
    "-isystem third_party/public"
)

$defines = @(
    "-DTRACY_ENABLE"
)

$includePaths = @(
    ".\include"
    ".\third_party\public"
)

$cppFiles = Get-ChildItem .\src -Filter *.cpp -Recurse |
    Select-Object -ExpandProperty FullName

$srcFiles = @(
    $cppFiles
    ".\out\TracyClient.o"
)

# raylib
$raylibDeps = @(
    "-lraylib"
    "-lopengl32"
    "-lgdi32"
    "-lwinmm"
)

# Tracy dependencies (Windows)
# se precisar buildar
#  g++ -c third_party/public/TracyClient.cpp -DTRACY_ENABLE -O3 -Ithird_party/public -o out/TracyClient.o
$tracyDeps = @(
    "-ldbghelp"
    "-lws2_32"
    "-lsecur32"
)

# build command

$includeArgs = $includePaths | ForEach-Object { "-I$_" }

$allArgs = @(
    $cppVersion
    $optLevel
    $warnings
    $defines
    "-o"
    $outputExe
    $srcFiles
    $includeArgs
    $raylibDeps
    $tracyDeps
)

$cmd = "$compiler $($allArgs -join ' ')"

Write-Host $cmd
Invoke-Expression $cmd

# clang-tidy

$toolchain = "--gcc-toolchain=C:/msys64/ucrt64/ -target x86_64-w64-mingw32"

$tidyCmd = "clang-tidy .\src\*.cpp --header-filter=`".*src.*`" -- $cppVersion $toolchain $includeArgs"
Write-Host $tidyCmd
Invoke-Expression $tidyCmd