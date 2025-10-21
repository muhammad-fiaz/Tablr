# Installation

## Download Pre-built Binaries

Download the latest release for your platform from [GitHub Releases](https://github.com/muhammad-fiaz/tablr/releases):

- **Linux**: `tablr-linux-x64.tar.gz`
- **Windows**: `tablr-windows-x64.zip`
- **macOS**: `tablr-macos-x64.tar.gz`

### Linux/macOS

```bash
tar -xzf tablr-linux-x64.tar.gz
sudo cp -r lib/* /usr/local/lib/
sudo cp -r include/* /usr/local/include/
```

### Windows

Extract the zip file and add the `lib` and `include` directories to your project paths.

## Using xmake (Recommended)

```bash
wget https://github.com/muhammad-fiaz/tablr/releases/download/v0.1.0/tablr-xmake-0.1.0.tar.gz
tar -xzf tablr-xmake-0.1.0.tar.gz
cd tablr-xmake-0.1.0
xmake install
```

Or add to your `xmake.lua`:

```lua
add_includedirs("/path/to/tablr/include")
add_linkdirs("/path/to/tablr/lib")
add_links("tablr")
```

## Using Conan

```bash
conan install tablr/0.1.0@
```

## Using vcpkg

```bash
vcpkg install tablr
```

## From Source

```bash
git clone https://github.com/muhammad-fiaz/tablr.git
cd tablr
xmake build
xmake install
```
