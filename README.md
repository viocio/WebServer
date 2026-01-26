# 🚀 WebServer – Custom HTTP Server in C++

A lightweight **HTTP/1.1 web server written from scratch in C++**, built using low-level system calls and designed for learning and experimentation.

This project exposes what really happens **under the hood** when a client communicates with a server using HTTP.

---

## ✨ Features

- Custom **HTTP/1.1 request parser**
- POSIX **TCP sockets**
- **Thread-per-client** concurrency model
- Support for **keep-alive** (multiple requests per connection)
- **Static file serving** (HTML, CSS, JS, etc.)
- **POST upload support**
- **DELETE support**
- Configurable **server IP, port, and working directory**
- Proper handling of HTTP status codes (200, 400, 404, 408, 500, 501)
- Simple and modular architecture

---

## 📦 How to Use

### 1️⃣ Clone the repository
```bash
git clone https://github.com/viocio/WebServer
cd WebServer
```

### 2️⃣ Build the project
```bash
make
```

### 3️⃣ Run the server
```bash
./main
```

---

## ⚙️ Runtime Configuration (Prompted at Startup)

When starting the server, you will be prompted to enter:

- **IP address** the server should listen on  
  (previously hard-coded, now configurable at runtime)
- **Port**
- **Maximum number of simultaneous clients**
- **Absolute or relative path** to the directory used as server root (`pathRelativ`)

Example:
```
IP: 192.168.1.42
Port: 8080
Max clients: 10
Website path: ./site/
```

The `pathRelativ` directory is used for:
- serving files via **GET**
- storing uploaded files via **POST**
- deleting files via **DELETE**

---

## 🌐 Accessing Your Website

Once the server is running, access it from any device in the same LAN:

```
http://IP_ADDRESS:PORT
```

Example:
```
http://192.168.1.42:8080
```

---

## 📤 HTTP Method Support

### ✅ GET
- Serves static files from `pathRelativ`
- Supports HTML, CSS, JS, images, etc.

### ✅ POST (File Upload)
Two supported variants:

1️⃣ Filename in URL  
```
POST /file.txt
```

2️⃣ Filename via custom header  
```
X-Filename: file.txt
```

Uploaded files are saved **inside `pathRelativ`**.

### ✅ DELETE
```
DELETE /file.txt
```
Deletes the specified file from `pathRelativ`.

---

## ⚠️ Error Handling

The server properly responds with standard HTTP status codes:

- **200 OK** – request successful
- **201 Created** – file uploaded
- **400 Bad Request** – invalid request or missing data
- **404 Not Found** – file or resource does not exist
- **408 Request Timeout** – incomplete POST body
- **500 Internal Server Error** – server-side failure
- **501 Not Implemented** – unsupported HTTP method

---

## 🛠️ Tech Stack

- **C++**
- **POSIX / UNIX sockets**
- **std::thread** multithreading
- **Custom HTTP/1.1 parsing**
- **Filesystem operations**

---

## 📚 Documentation & Video Series

A complete step-by-step documented implementation (Romanian) is available here:

🎥 **YouTube playlist**  
https://www.youtube.com/playlist?list=PLQLV8c-gyK0D5ML5rgiVpiWh6SSq50mpI

---

## 🧠 Project Purpose

This project is designed as a **learning exercise** to understand:

- how TCP servers accept and manage connections
- multithreading and concurrency
- manual HTTP request parsing
- building valid HTTP responses
- serving and manipulating files via HTTP

It provides a strong foundation for future work in:
- networking
- backend systems
- operating systems
- cybersecurity

---

## 🤝 Contributing

Contributions, suggestions, and improvements are welcome.  
Feel free to open an issue or submit a pull request.
