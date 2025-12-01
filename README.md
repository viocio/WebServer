# 🚀 WebServer – Custom HTTP Server in C++

A lightweight web server written **from scratch in C++**, featuring:

- a custom HTTP/1.1 parser  
- POSIX sockets  
- multithreading  
- serving static files  
- simple and modular architecture  

This project is designed to help you understand what really happens under the hood when a client sends an HTTP request to a server.

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

### 4️⃣ Provide the required parameters
When prompted, enter:

- the **port** the server should listen on  
- the **maximum number of simultaneous clients**  
- the **absolute path** to the directory where your website files are located  

---

## 🌐 Accessing Your Website

Once the server is running, you can access your website from any device in the same LAN:

```
http://IP_ADDRESS:PORT
```

Where:

- `IP_ADDRESS` = the IP address of the machine running the server  
- `PORT` = the port you selected at startup  

Example:
```
http://192.168.1.42:8080
```

---

## 📚 Full Documentation & Video Series

A complete, step-by-step documented implementation is available here:

🎥 YouTube playlist:  
https://www.youtube.com/playlist?list=PLQLV8c-gyK0D5ML5rgiVpiWh6SSq50mpI

---

## 🛠️ Tech Stack

- **C++**
- **POSIX / UNIX sockets**
- **pthread multithreading**
- **Custom HTTP/1.1 parsing**
- **Static file serving**

---

## 🧠 Project Purpose

This project is built as a learning exercise to understand:

- how TCP servers accept and manage connections  
- how to implement multithreading  
- how to parse HTTP requests manually  
- how to construct and send valid HTTP responses  
- how to serve static files from the filesystem  

It is an excellent foundation for further work in networking, backend development, or cybersecurity.

---

## 🤝 Contributing

Contributions, suggestions, and improvements are welcome.  
Feel free to open an issue or submit a pull request.

