# ESP32 Webserver

_A web server running from an Espressif ESP32._

Goals:
- The goal of this project is to gain an understanding of the interface between a microcontroller and the networking systems that are used in every-day life.

Constraints:
- Low-lib approach
- No Arduino IDE or software
- No re-inventing the wheel, unless it's interesting

Capital Costs:
- ESP32-S3-DevKitC-1-N32R8V Development Board ~$18.00

---

As you gain more experience in embedded software, you may be drawn to step away from Arduino/Raspberry Pi in favor of a more specialized and less kid friendly version, however tutorials such as https://randomnerdtutorials.com/esp32-web-server-arduino-ide/ provide no critical thinking challenges to the developer and allow prospective software engineers to pad their resumes with half baked projects (I see that its on your resume, but can you talk about it?). Playing devil’s advocate for this example, I have heard the phrase “You wouldn’t build the Eiffel tower with toothpicks.” Meaning we shouldn’t be wasting time on needlessly complicated tasks if the time that it takes to perform the action outweighs the knowledge that we gain. To strike this balance, I installed hard limits in both directions for this project:

- Use as few pre-compiled libraries
- Work as hard as you believe the industry works and nothing more

This project is not a tutorial as it would create a similar situation for you that I’m trying to avoid. Rather it is a progression tracker for how one might go about following this process from scratch.

## Project Info

Warning: Ensure to hide Public IP, SSID, and Password

## Proof of Concept

![image](https://github.com/user-attachments/assets/ec1851f6-9992-4c9e-9505-961348ca428b)
![IMG_3983](https://github.com/user-attachments/assets/3ebe019a-e2da-4b84-8e43-db375c6fdb98)

## Notes if you wanted to replicate this project

You should start looking through the documentation that is available for the ESP32. This can be found by googling “ESP32 Documentation” and choosing https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/get-started/index.html. Reading through, you can see the requirements that the example projects need. For this project, in-depth knowledge of the ESP 32 is not necessarily required, as we can use the documented examples to help us get started. (If we were running a more technical project, we would likely be pouring over this website to ensure that all the technical requirements are met)

I will be programming my ESP32 through a Raspberry Pi running Debian GNU/Linux 12 (bookworm) aarch64. Pages like https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/linux-macos-setup.html will be used to assist setup. I will not write out the specific commands (You should look in the documentation) that I ran on my machine because they are easily available on the website via the above link. If you are absolutely lost during this process, a resource that may provide some insight into this project is https://www.youtube.com/watch?v=dOVjb2wXI84&t=290s

The ESP framework is built on Python, and that’s great if you want a simple approach, but if you’re like me, you’ll want to code in something like C/C++. You may know the C language fairly well, but whenever you start a project on a specific platform, it's not necessary to memorize every API of that platform, so going to the API reference pages is very important: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/index.html

The crux of our project is found here: https://github.com/espressif/esp-idf/blob/9106c43accd9f5e75379f62f12597677213f5023/examples/protocols/http_server/simple/main/main.c
I highly recommend jumping around because there’s a lot to learn if you’re new to the inner workings of HTTP. I feel that the code that is in use in repositories like this is perfectly allowed for this project, as it was provided directly from the framework’s manufacturer. 

After looking through the simple HTTP server example, you should have a general idea about how the programs are structured in terms of URI handling. Now you can take a look at the https://github.com/espressif/esp-idf/tree/master/examples/protocols/http_server/file_serving example. This will detail not only how to respond to GET and POST for content, but also how to serve an HTML file to the connected client.

Another tip that I would give is to compare what your project looks like with what other examples of projects look like. For example, the idf_component.yml file that I was missing caused me to not be able to include a dependency and fail to build.
Ensure that if you copy this build, you do not push the sdkconfig file to GitHub. This file is essentially where your environment variables, like the Wi-Fi password and SSID, are stored.

I was able to get everything working correctly by constructing my program based on both https://github.com/espressif/esp-idf/tree/master/examples/protocols/http_server/file_serving and https://github.com/espressif/esp-idf/tree/9106c43accd9f5e75379f62f12597677213f5023/examples/protocols/http_server/simple 

The code that I worked on can be found in the main directory of this repo.

## References
- https://github.com/espressif/esp-idf
- https://www.youtube.com/watch?v=dOVjb2wXI84&t=290s
- https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32s3/esp32-s3-devkitc-1/user_guide.html#getting-started
- https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/linux-macos-setup.html
- https://randomnerdtutorials.com/esp32-web-server-arduino-ide/
