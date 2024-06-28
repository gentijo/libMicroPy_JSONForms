# MicroPython JSONForms
## Problem statemwent
Producing embedded interactive displays can be challenging. Micropython JSON Forms includes a web based drag and drop GUI editor that produces JSON data that describes the form. This form data can then be used in a renderer to provide a cross platform, implementation non specific, interactive. The renderer in this package supports the [LVGL](https://lvgl.io/) graphics library, which is supported by many platforms. 

## What is JSONForms ?
[JSONForms](https://jsonforms.io/) is a Web based standard that allows you to create a Web based data entry form using a friendly drag and drop editor, that produces JSON output files.  These output files can be used in a JSONForms renderer to render the form on various platforms (React.js & VUE.js) making it very easy for developers and end users to create new forms with very little technical knowledge. 

There are several Open Source editors that will be used as seed projects that can support embedded vs web based display editor.

Two examples of existing editors are:
### [JSONForms by Eclipse]
- [Live Editor](https://jsonforms-editor.netlify.app)
- [Source Code](https://github.com/eclipsesource/jsonforms-editor)

### Aurelia by FormIO, currently it's a archive project but is still relevent as a starter project
- [Live Editor](https://formio.github.io/aurelia-formio)
- [Source Code](https://github.com/gentijo/aurelia-formio)

## What is Micropython JSON Forms ?
Micropython JSON Forms is a JSONForms LVGL renderer that is configured to be a Micropython C User module

It leverages the new cost effective ESP32 LCD displays such as

[Alliexpress LCD Display](https://www.aliexpress.us/item/3256804913729039.html)

[Amazon LCD Display](https://www.amazon.com/ELECROW-Touchscreen-Monitor-800x480-ESP32-S3-WROOM/dp/B0C8T9VSMB/)

Test code and JSONForm are available here [JSONForms Test](py/JSONForms/tests/)