[![Build Status][travis-badge]][travis-link]

# Hydra

Hydra is a package for generating toys that is fast, easily configurable and hopefully user friendly.

## Compilation

First clone the respository,

```bash
git clone https://github.com/eddieshields/ToyGenerator.git
```

If you are on lxplus, for a simple build just call

```bash
source build.sh
```

Otherwise see [Compilation](doc/READMEs/compilation.md) for more details.

Each time you log back in call ```. setup.sh``` from the repository root.

## Interactive Hydra

Hydra can be used in an interactive python session. Simply call

```bash
Hydra
```

from the directory root to load and interactive python session with Hydra pre-configured. You can
additionally call options files this way by

```bash
Hydra path/to/options/file
```

## Configuration

Hydra works on the basis of a series of algorithms acting on an event.
The easiest way to configure a sequence is by writing an options file, more details on this is given is [Configuration](doc/READMEs/configuration.md).

[travis-badge]:      https://travis-ci.com/eddieshields/ToyGenerator.svg?token=kSjk97VeMvMyZGvyxnp2&branch=main
[travis-link]:       https://travis-ci.com/github/eddieshields/ToyGenerator