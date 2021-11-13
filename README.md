![license](https://img.shields.io/github/license/fedddddd/t7-mod.svg)
[![open bugs](https://img.shields.io/github/issues/fedddddd/t7-mod/bug?label=bugs)](https://github.com/fedddddd/t7-mod/issues?q=is%3Aissue+is%3Aopen+label%3Abug)
[![Build status](https://ci.appveyor.com/api/projects/status/2hpepp6772r8u680?svg=true)](https://ci.appveyor.com/project/fedddddd/t7-mod)

# T7: Mod
<p align="center">
  <img src="assets/github/banner.png?raw=true" />
</p>

<br/>

## Download

- **[Click here to get the latest release](https://ci.appveyor.com/api/projects/fedddddd/t7-mod/artifacts/build%2Fbin%2Fx64%2FRelease%2Ft7-mod.exe?branch=main&job=Environment%3A%20APPVEYOR_BUILD_WORKER_IMAGE%3DVisual%20Studio%202019%2C%20PREMAKE_ACTION%3Dvs2019%2C%20CI%3D1%3B%20Configuration%3A%20Release)**
- **You will need to drop this in your Call of Duty Black Ops III/UnrankedServer installation folder. If you don't have Call of Duty Black Ops III, get those game files first.**

## Compile from source

- Clone the Git repo. Do NOT download it as ZIP, that won't work.
- Update the submodules and run `premake5 vs2019` or simply use the delivered `generate.bat`.
- Build via solution file in `build\t7-mod.sln`.

### Premake arguments

| Argument                    | Description                                    |
|:----------------------------|:-----------------------------------------------|
| `--copy-to=PATH`            | Optional, copy the EXE to a custom folder after build, define the path here if wanted. |
| `--dev-build`               | Enable development builds of the client. |

<br/>

## Disclaimer

This software has been created purely for the purposes of
academic research. It is not intended to be used to attack
other systems. Project maintainers are not responsible or
liable for misuse of the software. Use responsibly.
