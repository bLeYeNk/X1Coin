Sample init scripts and service configuration for x1coind
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/x1coind.service:    systemd service unit configuration
    contrib/init/x1coind.openrc:     OpenRC compatible SysV style init script
    contrib/init/x1coind.openrcconf: OpenRC conf.d file
    contrib/init/x1coind.conf:       Upstart service configuration file
    contrib/init/x1coind.init:       CentOS compatible SysV style init script

Service User
---------------------------------

All three Linux startup configurations assume the existence of a "x1coin" user
and group.  They must be created before attempting to use these scripts.
The macOS configuration assumes x1coind will be set up for the current user.

Configuration
---------------------------------

Running x1coind as a daemon does not require any manual configuration. You may
set the `rpcauth` setting in the `x1coin.conf` configuration file to override
the default behaviour of using a special cookie for authentication.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that x1coind and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If x1coind is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running x1coind without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see `share/examples/x1coin.conf`.

Paths
---------------------------------

### Linux

All three configurations assume several paths that might need to be adjusted.

    Binary:              /usr/bin/x1coind
    Configuration file:  /etc/x1coin/x1coin.conf
    Data directory:      /var/lib/x1coind
    PID file:            /var/run/x1coind/x1coind.pid (OpenRC and Upstart) or
                         /run/x1coind/x1coind.pid (systemd)
    Lock file:           /var/lock/subsys/x1coind (CentOS)

The PID directory (if applicable) and data directory should both be owned by the
x1coin user and group. It is advised for security reasons to make the
configuration file and data directory only readable by the x1coin user and
group. Access to x1coin-cli and other x1coind rpc clients can then be
controlled by group membership.

NOTE: When using the systemd .service file, the creation of the aforementioned
directories and the setting of their permissions is automatically handled by
systemd. Directories are given a permission of 710, giving the x1coin group
access to files under it _if_ the files themselves give permission to the
x1coin group to do so. This does not allow
for the listing of files under the directory.

NOTE: It is not currently possible to override `datadir` in
`/etc/x1coin/x1coin.conf` with the current systemd, OpenRC, and Upstart init
files out-of-the-box. This is because the command line options specified in the
init files take precedence over the configurations in
`/etc/x1coin/x1coin.conf`. However, some init systems have their own
configuration mechanisms that would allow for overriding the command line
options specified in the init files (e.g. setting `X1COIND_DATADIR` for
OpenRC).

### macOS

    Binary:              /usr/local/bin/x1coind
    Configuration file:  ~/Library/Application Support/X1coin/x1coin.conf
    Data directory:      ~/Library/Application Support/X1coin
    Lock file:           ~/Library/Application Support/X1coin/.lock

Installing Service Configuration
-----------------------------------

### systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start x1coind` and to enable for system startup run
`systemctl enable x1coind`

NOTE: When installing for systemd in Debian/Ubuntu the .service file needs to be copied to the /lib/systemd/system directory instead.

### OpenRC

Rename x1coind.openrc to x1coind and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/x1coind start` and configure it to run on startup with
`rc-update add x1coind`

### Upstart (for Debian/Ubuntu based distributions)

Upstart is the default init system for Debian/Ubuntu versions older than 15.04. If you are using version 15.04 or newer and haven't manually configured upstart you should follow the systemd instructions instead.

Drop x1coind.conf in /etc/init.  Test by running `service x1coind start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

### CentOS

Copy x1coind.init to /etc/init.d/x1coind. Test by running `service x1coind start`.

Using this script, you can adjust the path and flags to the x1coind program by
setting the X1COIND and FLAGS environment variables in the file
/etc/sysconfig/x1coind. You can also use the DAEMONOPTS environment variable here.

### macOS

Copy org.x1coin.x1coind.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.x1coin.x1coind.plist`.

This Launch Agent will cause x1coind to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run x1coind as the current user.
You will need to modify org.x1coin.x1coind.plist if you intend to use it as a
Launch Daemon with a dedicated x1coin user.

Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
