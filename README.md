**REMINDWare**  
| [**About REMIND**](#about-REMIND)  
| [**IBCCM Installation**](#IBCCM-Installation)  
| [**Getting started**](#getting-started)  
| [**API Reference**](#API-Reference)  

![generalized distributed system](https://www.hanglok-tech.cn/Template/Home/img/introduction-banner-02.jpg)

**REMINDware** is a middleware designed for the development of intervention surgical robots. To facilitate communication with interested peers about the development of intervention surgical robot technology, we encapsulate the REMINDware design concept into middleware. As the development iterations of this project are still progressing in an orderly manner, only the early C++ version library files are currently publicly available, supporting the rapid construction of a distributed node communication architecture under the Qt C++ environment. This repository provides dynamic/static library files for Linux/Windows, a central node container image, simple dual-node communication examples, and relevant installation and usage instructions.

| :warning: Information for end users |
|:------------------------------------|
| The REMINDWare is currently under active development, and the provided library files in this repository are for trial use only, facilitating communication and collaboration among interested developers. The latest version will be available soon. |

## About REMIND

**REMIND** has proposed a design paradigm for intervention surgical robots, as shown in the following figure：
![design paradigm](https://www.hanglok-tech.cn/Template/Home/img/liena-pic-n-12.png)
Within this paradigm, intervention surgical robots conform to the design principles of distributed robotics and can be abstracted into the following main nodes：

- Interventionalist’s brain-like cloud computing module (**IBCCM**)
This module is as the brain of interventionalists with self-learning ability, burdening the responsibility of restoring and distributing information as well as integrating all algorithms;
- Interventional planning information generating module (**IPGM**)
During the implementation of interventional surgery, this module enables surgeons to interact with IBCCM to generate a collection of planning information;
- Immersive control & navigation module (**ICNM**)
This module receives the planned information from IPGM and interventional physicians could initiate or terminate every surgical action;
- Interventional tool sensing module (**ITSM**)
This module gathers perception information about all intraoperative actions and related outcomes, which are sent to ICNM for immersive presentation;
- Interventional tool execution module (**ITEM**)
This module collaborates with physicians to execute actions according to IBCCM’s control commands.

Please, refer to the REMIND information page for a more detail：[REMIND-OS](https://www.hanglok-tech.cn/list/55.html).

## IBCCM Installation
[install IBCCM docker image](document/IBCCM_installation.txt)<br>

## Node And Topology Editor
[Node And Topology Editor](document/topology_editor.txt)<br>

## Getting Started
[Quick start](document/quick_start.txt)<br>
[Example](document/run_example.txt)<br>

## API Reference
[APIs](document/api_documentation.txt)<br>