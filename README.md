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

## References
https://github.com/espressif/esp-idf
https://www.youtube.com/watch?v=dOVjb2wXI84&t=290s
https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32s3/esp32-s3-devkitc-1/user_guide.html#getting-started
https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/linux-macos-setup.html
https://randomnerdtutorials.com/esp32-web-server-arduino-ide/
