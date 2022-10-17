# ServiceControl

ServiceControl is currently nothing but an empty UI. Sorry.

ServiceControl aims to be a GUI that allows you to visually inspect and action systemd units, locally and remotely.

In order to make it as flexible as possible, the architecture has a bit of extra indirection. Instead of calling the DBus interfaces directly, the servicecontrol-worker process will service commands from the servicecontrol UI, speaking Cap'n'proto over stdin and stdout. Anything that could pipe stdin or stdout - including SSH - could be used to handle remoting to a server.
