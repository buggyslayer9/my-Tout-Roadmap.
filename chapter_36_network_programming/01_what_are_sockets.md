# 32.1 The Network is Just a File: Introduction to Sockets

We have covered the UNIX philosophy: "Everything is a file."
You read from hardware devices using `read(/dev/sda)`.
You read kernel state using `read(/proc/meminfo)`.
You pass data between processes using an anonymous Pipe, reading its File Descriptor.

So, how do you talk to an entirely different computer across the Atlantic Ocean?
You open a special file descriptor called a **Socket**, and you use the exact same `read()` and `write()` calls you use for text files.

## The Socket System Call

A socket is an endpoint for communication. When you create a socket, the Kernel gives your program a standard integer File Descriptor. 

There are two primary protocols we use with network sockets: **TCP** and **UDP**.

## 1. TCP (Transmission Control Protocol)
*   **Analogy:** A phone call.
*   **Behavior:** Connection-Oriented.
*   **Guarantees:** 100% reliable. The order of bytes is guaranteed. If a byte is lost during transmission across the internet, the sender's Kernel automatically detects it and resends it. The receiver will explicitly wait for the missing byte before handing any data to the User Space application.
*   **Use Cases:** Web pages (HTTP), SSH shells, Chat apps (where sequence and missing data is lethal).
*   **Cost:** "Slow." Establishing the connection requires a 3-way handshake before a single byte of actual data is sent. High overhead per packet to track order and delivery.

## 2. UDP (User Datagram Protocol)
*   **Analogy:** Sending a postcard in the mail.
*   **Behavior:** Connectionless.
*   **Guarantees:** Absolutely zero. No guarantee the packet arrives. No guarantee that if you send Packet A then Packet B, they will arrive in that order (Packet B might take a faster fiber link across the ocean and arrive first).
*   **Use Cases:** Multiplayer video games, Live video streaming, Voice calls.
*   **Why would anyone use this?** It is incredibly fast. If you are playing a first-person shooter at 60 Frames Per Second, the server is sending you your position 60 times a second. If frame 3 gets lost, *you do not want the game to stop and ask for a resend*. By the time the resend arrives, frame 4, 5, and 6 are already here! Just drop frame 3 and keep moving.

## Network Byte Order (Big Endian)

There is one critical issue when sending raw bytes across the internet. 

Your PC (x86_64) uses **Little-Endian** byte ordering. This means the number `0x1234` is stored in RAM as `[34] [12]`.
But what if the server you are talking to is an old IBM mainframe that uses **Big-Endian** (`[12] [34]`)? 

If you send raw bytes of an integer over a socket, the IBM mainframe will read the integer completely backwards!

To solve this, the Internet formally standardized **Network Byte Order**, which is Big-Endian.

As a Systems Programmer, you must **never** send an integer over a socket without explicitly converting it to Network Byte Order first. You do this using standard POSIX functions provided by `<arpa/inet.h>`:

*   `htons(x)`: **H**ost **TO** **N**etwork **S**hort (16-bit, useful for Port numbers)
*   `htonl(x)`: **H**ost **TO** **N**etwork **L**ong (32-bit, useful for IP addresses)
*   `ntohs(x)`: **N**etwork **TO** **H**ost **S**hort (Converts it back when you receive it)
*   `ntohl(x)`: **N**etwork **TO** **H**ost **L**ong (Converts it back when you receive it)

If you forget to call `htons(8080)` when specifying your server port, the Kernel will open your server on a completely random, garbage port number because the byte order is reversed!
