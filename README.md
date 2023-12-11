# Example of Authorization in SSO Eve Online Using Qt and C++

## General Description
This is a sample project demonstrating how to perform SSO authorization for Eve Online using Qt and C++. The project follows the guidelines provided in the Eve Online [ESI documentation](https://docs.esi.evetech.net). It can be compiled for Android (x86, x86-64, arm64-v8a, armeabi-v7a) and desktop (64-bit) platforms. The application authenticates via SSO and displays information such as access_token, refresh_token and etc., for further use Eve Online API.

The project utilizes OpenSSL 1.1.x (shared for Android and static for desktop) and includes the header-only [jwt-cpp library](https://github.com/Thalhammer/jwt-cpp). You don't need to install anything from these dependencies as they are built into this project.

### Requirements
- Qt 6.2 with Android support
- Basic STL (Standard Template Library) support
- A compiler supporting at least C++11

### How to Start
1. Create your app at https://developers.eveonline.com with a Callback URL of http://localhost:8080/oauth-callback.
2. After that, you will need to change two lines in `main.cpp` (enter your Client ID and Scopes). By default, they are empty. 

    ![main](./data/github/Screenshot%20from%202023-07-28%2017-58-10.png)

3. Run the project via Qt Creator or the console. You will see a window with a button in the center (if it is the desktop platform) or an application (if it is Android). Click on it, and you will be redirected to the browser to log in. If this step is successful, the console will display the information received during the authorization process.

4. [NOT NECESSARY!!!] If you want to use your own Callback URL, change the line in the `Authorization_engine.h` file:
```c++
    QUrl Callback_URL = QString("<your Callback URL>");
```
and into `Tcp_server.cpp` number 8080 (it's port by default) on your castom port from Callback_URL.

```c++
    void Tcp_server::run_Tcp_server()
{
    if (listen(QHostAddress::Any, <your port>)){
        return;
    }
    else {
        // TODO
        throw std::runtime_error("server dosen't run");
        return;
    }
}
```
 Thats's all !
