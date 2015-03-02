# website-pdf-snapshot-taker
A small gui interface to a phantomjs script (uses a modified phantomjs build(so the media query print is not set))


# how to build :
on debian or ubuntu install libfltk1.3-dev and run
fltk-config --compile htmltopdf.cpp


the phantomjs binary is compiled from the official source code, following their official guide. The only difference is that you have to comment out line 1501 in phantomjs/src/qt/qtwebkit/Source/WebCore/page/FrameView.cpp ( setMediaType("print"); ). Here is the surrounding code:

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
