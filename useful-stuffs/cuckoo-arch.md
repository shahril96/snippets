# Cuckoo Sandbox in Arch Linux

## Requirements


The Cuckoo host components is completely written in Python, therefore it is required to have an appropriate version of Python installed. At this point we only fully support Python 2.7. Older version of Python and Python 3 versions are not supported by us (although Python 3 support is on our TODO list with a low priority).

The following software packages from the apt repositories are required to get Cuckoo to install and run properly:


```
$ sudo pacman -S python2 python2-pip libffi openssl
$ sudo pip2 install virtualenv setuptools
$ sudo pacman -S libjpeg-turbo swig zlib
```

In order to use the Django-based Web Interface, MongoDB is required:

`$ sudo pacman -S mongodb`

In order to use PostgreSQL as database (our recommendation), PostgreSQL will have to be installed as well:

`$ sudo pacman -S postgresql`

Yara and Pydeep are optional plugins, which you can install using below commands:

`$ pacaur -S python2-pydeep yara`

If you want to use the mitm auxiliary module (to intercept SSL/TLS generated traffic), you need to install mitmproxy. You can do so by installing it using pacman.

`$ sudo pacman -S mitmproxy`


### Virtualization Software

Cuckoo Sandbox supports most Virtualization Software solutions. As you will see throughout the documentation, Cuckoo has been setup to remain as modular as possible and in case integration with a piece of software is missing this could be easily added.

For the sake of this guide we will assume that you have VirtualBox installed (which is the default), but this does not affect the execution and general configuration of the sandbox.

You are completely responsible for the choice, configuration, and execution of your virtualization software. Please read our extensive documentation and FAQ before reaching out to us with questions on how to set Cuckoo up.

In case you want to proceed with virtualbox, you can install into your Arch as below:

`$ sudo pacman -S virtualbox virtualbox-guest-iso virtualbox-guest-utils`

### Installing Volatility

Volatility is an optional tool to do forensic analysis on memory dumps. In combination with Cuckoo, it can automatically provide additional visibility into deep modifications in the operating system as well as detect the presence of rootkit technology that escaped the monitoring domain of Cuckoo’s analyzer.

In order to function properly, Cuckoo requires at least version 2.3 of Volatility, but recommends the latest version, Volatility 2.6.

You can install volatility using AUR script:

`$ sudo pacman -S volatility`


### Installing tcpdump

In order to dump the network activity performed by the malware during execution, you’ll need a network sniffer properly configured to capture the traffic and dump it to a file.

By default Cuckoo adopts tcpdump, the prominent open source solution.

Install it on Arch:

`$ sudo pacman -S tcpdump`

By default it requires root to operate with, we can set the binary so that it can able to runs with normal user privileges:

```
$ sudo setcap cap_net_raw,cap_net_admin=eip /usr/bin/tcpdump
```

### Installing M2Crypto

Currently the M2Crypto library is only supported when SWIG has been installed. It can be done as follows:

` $ sudo pip2 install m2crypto`

## Installing Cuckoo

### Create a user

You can either run Cuckoo from your own user or create a new one dedicated just for your sandbox setup. Make sure that the user that runs Cuckoo is the same user that you will use to create and run the virtual machines (at least in the case of VirtualBox), otherwise Cuckoo won’t be able to identify and launch these Virtual Machines.

Create a new user:

`$ sudo useradd cuckoo`

If you’re using VirtualBox, make sure the new user belongs to the “vboxusers” group (or the group you used to run VirtualBox):

`$ sudo usermod -a -G vboxusers cuckoo`

### Install Cuckoo

Installing the latest version of Cuckoo is as simple as follows.

```
$ sudo pip2 install -U pip setuptools
$ sudo pip2 install -U cuckoo
```

Although the above, a global installation of Cuckoo in your OS works mostly fine, we highly recommend installing Cuckoo in a virtualenv, which looks roughly as follows:

```
$ virtualenv venv
$ . venv/bin/activate
(venv) $ pip2 install -U pip setuptools
(venv) $ pip2 install -U cuckoo
```

Some reasons for using a virtualenv:

* Cuckoo’s dependencies may not be entirely up-to-date, but instead pin to a known-to-work-properly version.
* The dependencies of other software installed on your system may conflict with those required by Cuckoo, due to incompatible version requirements (and yes, this is also possible when Cuckoo supports the latest version, simply because the other software may have pinned to an older version).
* Using a virtualenv allows non-root users to install additional packages or upgrade Cuckoo at a later point in time.
* And simply put, virtualenv is considered a best practice.