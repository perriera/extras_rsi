## HOWTO-RSI.md (rsi_server/rsi_client)

**RSI: Remote Service Invocation**
This is the primary utility used to create services on a remote server for RSI.

**_Who would want to use this?_**
Anybody that wishes to run proprietary software on a remote server while protecting proprietary software on the local client machine. For example, in the case of FreeFormJS.org, (the originator of this package), the client can now safely have all of their proprietary source code stripped out before uploading to the FreeFormJS.org website, (where it is processed using proprietary software) and then automatically downloaded back again to the client.

## rsi_server

Specify the ip address and port and a range of available ports for use by the rsi_client.

    build/rsi_server 127.0.0.1:8080 9000-9500

## rsi_client

Specify the ip address and port of the rsi_server and then specify the files to be uploaded to that server.

    build/rsi_client 127.0.0.1:8080 testit/src.zip testit/exparx.webflow.zip

**Note**: There must be at least one file to be processed.
**Note**: Technically, you can have as many extras files as the command line will allow.

### -help

> Displays this help text, (provided the file is in the same directory).

## Summary

This utility will allow you to run proprietary software on a remote server while protecting proprietary software on the local client machine.
