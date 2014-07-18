# ltsview

[LTSV](http://ltsv.org/) viewer by C language

## Installation

```sh
$ git clone https://github.com/DQNEO/c-ltsview.git
$ cd c-ltsview
$ make
```

## Usage

```sh
$ cat access.log | ltsview
```

```sh
$ cat access.log | ltsview -k key1,key2
```

## Options

### -k

select by keys.

```sh
$ printf 'l1:v1\tl2:v2\nl3:v3' | ltsview
---
l1: v1
l2: v2
---
l3: v3
$ printf 'l1:v1\tl2:v2\nl3:v3' | ltsview -k l1,l3
---
l1: v1
---
l3: v3
```

### -h, --help

show usage.

### -v, --version

show version.

## License

GPLv2

