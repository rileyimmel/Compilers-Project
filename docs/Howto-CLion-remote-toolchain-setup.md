# CLion remote toolchain for tipc developemnt on HPC cluster

> CLion 2022.3.2 | Build #CL-223.8617.54, built on January 25, 2023
>
> macOS Ventura 13.5 (22G74)

## STEP 1: Setup .bashrc in UVa CS Portal

1. Log-in to your portal shell using your terminal.
2. Add the following as-it-is to the end of your .bashrc file in your home directory

```shell
#tipc ENV setup
export PATH="/sw/ubuntu-22.04/cmake/current/bin:/sw/ubuntu-22.04/llvm/14.0.6/bin:$PATH"
export LD_LIBRARY_PATH="/sw/ubuntu-22.04/llvm/14.0.6/lib"
export LD_INCLUDE_PATH="/sw/ubuntu-22.04/llvm/14.0.6/include"
alias antlr4="java -Xmx500M -cp /sw/ubuntu-22.04/antlr/current org.antlr.v4.Tool"
alias grun="java -Xmx500M -cp /sw/ubuntu-22.04/antlr/current org.antlr.v4.gui.TestRig"
export CLASSPATH="/sw/ubuntu-22.04/antlr/current"
export TIPCLANG=`which clang`
```

OR

execute the following in your shell:

```shell
echo "I3RpcGMgRU5WIHNldHVwCmV4cG9ydCBQQVRIPSIvc3cvdWJ1bnR1LTIyLjA0L2NtYWtlL2N1cnJlbnQvYmluOi9zdy91YnVudHUtMjIuMDQvbGx2bS8xNC4wLjYvYmluOiRQQVRIIgpleHBvcnQgTERfTElCUkFSWV9QQVRIPSIvc3cvdWJ1bnR1LTIyLjA0L2xsdm0vMTQuMC42L2xpYiIKZXhwb3J0IExEX0lOQ0xVREVfUEFUSD0iL3N3L3VidW50dS0yMi4wNC9sbHZtLzE0LjAuNi9pbmNsdWRlIgphbGlhcyBhbnRscjQ9ImphdmEgLVhteDUwME0gLWNwIC9zdy91YnVudHUtMjIuMDQvYW50bHIvY3VycmVudCBvcmcuYW50bHIudjQuVG9vbCIKYWxpYXMgZ3J1bj0iamF2YSAtWG14NTAwTSAtY3AgL3N3L3VidW50dS0yMi4wNC9hbnRsci9jdXJyZW50IG9yZy5hbnRsci52NC5ndWkuVGVzdFJpZyIKZXhwb3J0IENMQVNTUEFUSD0iL3N3L3VidW50dS0yMi4wNC9hbnRsci9jdXJyZW50IgpleHBvcnQgVElQQ0xBTkc9YHdoaWNoIGNsYW5nYAoK" | base64 -d >>~/.bashrc
```

## STEP 2: Setup SSH profile

1. Open CLion, goto `Settings | Tools | SSH Configurations` and click `+` to add new configuration
2. Fill in your portal credentials and make sure rest of your configuration looks like the following:
   ![ssh-add.png](clion-remote-dev-img%2Fssh-add.png)
   _NOTE: Use YOUR computing ID in `Username` field_

3. Click `Test Connection` and you should see `Successfully connected!` as following -

![ssh-Okay-connect.png](clion-remote-dev-img%2Fssh-Okay-connect.png)

## STEP 3: Setup remote toolchain

1. Go to `Settings | Build, Execution, Deployment | Toolchains` and click `+` icon and select Remote Host from the
   drop-down menu to create a new toolchain.

![add-remote.png](clion-remote-dev-img%2Fadd-remote.png)

2. Existing SSH configurations are available from the drop-down list. To add a new configuration click the gear icon
   next to the Credentials field. In the dialog that opens, choose your previously created SSH configuration.

![remote-portal-config.png](clion-remote-dev-img%2Fremote-portal-config.png)

## STEP 4: Create a corresponding CMake profile

1. Go to `Settings | Build, Execution, Deployment | CMake`
2. Click `+` to create a new CMake profile, then select your Remote Toolchain from the dropdown after `Toolchain`
   section.

![cmake-toolchain-select.png](clion-remote-dev-img%2Fcmake-toolchain-select.png)

3. Make sure that other parameters match the following -
   ![remote-cmake-configuration.png](clion-remote-dev-img%2Fremote-cmake-configuration.png)

## STEP 5: Change the remote root path and project directory mapping

1. Go to `Settings | Build, Execution, Deployment | Deployment` and change the following fields in the `Connection`
   tab of your remote toolchain-
    1. Type = SFTP
    2. Choose your tipc SSH configuration created in _**Step 2**_ from the drop-down selector.
    3. Click `Autodetect` button in `Root Path` field.
       > This should populate the corresponding text field with your Portal home directory, which should
       be `/u/<your computing ID>`
       >
       > Otherwise, type it manually in the text field. You can check your home directory by logging in the portal via
       SSH using your terminal and executing `echo $HOME` in your portal shell.
    4. Check `Use Rsync` checkbox.

![Remote-root-dir.png](clion-remote-dev-img%2FRemote-root-dir.png)

2. Click `Mappings` tab and make the following changes -
    1. Local path = tipc direcory in your local computer, you can get this by opening a terminal in your local tipc
       folder and executing `pwd`.

   ![tipc-pwd.png](clion-remote-dev-img%2Ftipc-pwd.png)

    2. Deployment path = "**/TIPCREMOTE**" (without double quotes).
   > _You can change it to anything else, as long as it is unique, and you have read/write/execute permission on it._

![Remote-dir-mapping.png](clion-remote-dev-img%2FRemote-dir-mapping.png)

3. Click `Apply` to save configuration and exit.

---

#### References

[1] [jetbrains.com/help/clion/remote-projects-support](https://www.jetbrains.com/help/clion/remote-projects-support.html)

[2] [jetbrains.com/help/clion/cmake-profile](https://www.jetbrains.com/help/clion/cmake-profile.html)

[3] [UVa CS portal wiki](https://www.cs.virginia.edu/wiki/doku.php?id=compute_portal)
