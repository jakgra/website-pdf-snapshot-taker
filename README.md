# website-pdf-snapshot-taker
A small gui interface to a phantomjs script (uses a modified phantomjs build(so the media query print is not set))


# how to build :

##First (on all supported OS):
Open a terminal and execute:
```
git clone https://github.com/jakgra/website-pdf-snapshot-taker.git
cd website-pdf-snapshot-taker
```
As an alternative you can download and extract the zip file.

##Then:
###on debian or ubuntu:
```
sudo apt-get install libfltk1.3-dev
fltk-config --compile htmltopdf.cpp
```
The compiled program is htmltopdf, for it to run correctly it must be located in the same folder as createPDF and phantomjs.

###on OSX:
install xcode
install fltk1.3 (instructions on their website)
```
fltk-config --compile htmltopdf.cpp && cp OSX/phantomjs htmltopdf.app/Contents/MacOS/phantomjs && cp createPDF.js htmltopdf.app/Contents/MacOS/createPDF.js
```
You get the folder(application) htmltopdf.app which you can directly use, copy, move from/to anywhere. 

###on windows:
TODO

##If you also wish to compile phantomjs:
the phantomjs binary is compiled from the official source code(v2.0.1), following their official guide. The only difference is that you have to comment out line 1501 in phantomjs/src/qt/qtwebkit/Source/WebCore/page/FrameView.cpp ( setMediaType("print"); ). Here is the surrounding code:

```
void FrameView::adjustMediaTypeForPrinting(bool printing)
{
    if (printing) {
        if (m_mediaTypeWhenNotPrinting.isNull())
            m_mediaTypeWhenNotPrinting = mediaType();
            //setMediaType("print");
    } else {
        if (!m_mediaTypeWhenNotPrinting.isNull())
            setMediaType(m_mediaTypeWhenNotPrinting);
        m_mediaTypeWhenNotPrinting = String();
    }
}
```

