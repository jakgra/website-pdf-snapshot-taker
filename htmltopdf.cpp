#include <stdio.h>			// fprintf()
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Native_File_Chooser.H>

Fl_Input *tofile;
Fl_Input *url;
Fl_Input *viewport_h;
Fl_Input *viewport_w;
Fl_Input *timeout;
int const maxPathSize=200;
char filename[maxPathSize];



void chooseFile( Fl_Widget* o, void*  ){
  Fl_Native_File_Chooser fnfc;
  fnfc.title("Pick a file");
  fnfc.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
  fnfc.filter("PDF files\t*.pdf\n");
  //fnfc.directory("/var/tmp"); // default directory to use
  // Show native chooser
  switch ( fnfc.show() ) {
  case -1: printf("ERROR: %s\n", fnfc.errmsg()); break; // ERROR
  case 1: printf("CANCEL\n"); break; // CANCEL
  default:
    printf("PICKED: %s\n", fnfc.filename());
    tofile->value(fnfc.filename());
    break; // FILE CHOSEN
  }
}

void createPDF( Fl_Widget* o, void*  ){
  /*printf("createPDF dela\n");
  char *str=new char[24];
  strcpy(str,"phantomjs createPDF.js ");
  strcat (str,url->value());
  strcat (str," \"");
  strcat (str,tofile->value());
  strcat (str,"\" ");
  strcat (str,viewport_w->value());
  strcat (str,"x");
  strcat (str,viewport_h->value());
  strcat (str," ");
  strcat (str,timeout->value());*/
  std::string str("phantomjs createPDF.js ");
  std::string str2( url->value() );
  std::string str3( tofile->value() );
  std::string str4( viewport_w->value() );
  std::string str5( viewport_h->value() );
  std::string str6( timeout->value() );
  std::string command( str+str2+" \""+str3+"\" "+str4+"x"+str5+" "+str6 );

  //str = "phantomjs createPDF.js " + (std::string) timeout->value()  + " ";

  //printf( "%s", command.c_str()  );
  int success=system( command.c_str() );
  if(success==0){
    //char filename[] = "defaults";


    FILE *file = fopen(filename, "w");


    if (file) {
      fputs((str2+"\n"+str4+"\n"+str5+"\n"+str6+"\n"+str3+"\n").c_str(), file);
    }
  }
}



void setDefaults(){
  // the file we want to read from
  //char filename[] = "defaults";


    std::ifstream ifs;
ifs.open (filename);



  if (ifs) {

    // set up the buffer to read the line into. Don't worry too much
    // if some of the lines are longer than 80 characters - the buffer
    // will be made bigger if need be.
    //size_t buffer_size = 80;
    std::string buffer;


    int i=0;

    while (std::getline( ifs, buffer )){
      switch ( i ) {  
      case 0:  url->value( buffer.c_str() );
      case 1: viewport_w->value( buffer.c_str() );
      case 2: viewport_h->value( buffer.c_str() );
      case 3: timeout->value( buffer.c_str() );
      case 4: tofile->value( buffer.c_str() );
      }
      i++;
    }
    ifs.close();
  }else{
    //char defaultoutputpdf[maxPathSize];
    //strcat( defaultoutputpdf, getenv("HOME"));
    //strcat( defaultoutputpdf, "/output.pdf");
    std::string str1(getenv("HOME"));
    std::string str2("/output.pdf");
    url->value("http://example.com/");
    viewport_w->value("1920");
    viewport_h->value("1080");
    timeout->value("300");
    tofile->value( (str1+str2).c_str() );
  }

}





int main(int argc, char **argv) {
  strcat(filename, getenv("HOME"));
  strcat(filename, "/.wpst-defaults");
  //printf("ROOT : %s\n", filename);

 //delete[] path;



  static int sirina_programa=500;
  static int visina_programa=700;
  static int sirina_inputa=200;
  static int visina_inputa=30;
  static int zamik_inputa=50;
  static int visina_description=20;
  static int space_height=30;
  static int description_font_size=10;
  
  Fl_Window *window = new Fl_Window(50,50,sirina_programa,visina_programa);
  
  Fl_Group *viewport = new Fl_Group(0,0,sirina_programa,visina_programa);
  Fl_Box *naslov = new Fl_Box(0,10,sirina_programa,visina_inputa,"Take a pdf snapshot of a webpage:");
  naslov->labelsize(22);
  url = new Fl_Input(sirina_programa-zamik_inputa-sirina_inputa,space_height+visina_inputa,sirina_inputa,visina_inputa,"Url:");
  Fl_Box *url_d = new Fl_Box(0,space_height+visina_inputa+visina_inputa,sirina_programa,visina_description,"Usage: https://www.example.com/");
  url_d->labelsize(description_font_size);
  //Fl_Input *urlnaslov = new Fl_Input(0,60,sirina_programa,visina_inputa,"Url:");
  viewport_w = new Fl_Input(sirina_programa-zamik_inputa-sirina_inputa,(space_height+visina_inputa)*2,sirina_inputa,visina_inputa,"Viewport width (in px):");
  viewport_h = new Fl_Input(sirina_programa-zamik_inputa-sirina_inputa,(space_height+visina_inputa)*3,sirina_inputa,visina_inputa,"Viewport height (in px):");
  timeout = new Fl_Input(sirina_programa-zamik_inputa-sirina_inputa,(space_height+visina_inputa)*4,sirina_inputa,visina_inputa,"Timeout:");
  Fl_Box *timeout_d = new Fl_Box(0,(space_height+visina_inputa)*4+visina_inputa,sirina_programa,visina_description,"Usage: website opened -> timeout (in ms) -> screenshot");
  timeout_d->labelsize(description_font_size);
  tofile = new Fl_Input(sirina_programa-zamik_inputa-sirina_inputa,(space_height+visina_inputa)*5,sirina_inputa,visina_inputa,"Save to file:");
  Fl_Button *choosefiles = new Fl_Button(sirina_programa+5-zamik_inputa,(space_height+visina_inputa)*5,zamik_inputa-10,visina_inputa,"...");
  choosefiles->callback(chooseFile);
  Fl_Box *tofile_d = new Fl_Box(0,(space_height+visina_inputa)*5+visina_inputa,sirina_programa,visina_description,"Usage: provide a valid file path for your OS.");
  Fl_Box *tofile_d2 = new Fl_Box(0,(space_height+visina_inputa)*5+visina_inputa+(description_font_size+2),sirina_programa,visina_description,"Examples: /home/goodguy/test.pdf or C:\\somefolder\\test.pdf");
  tofile_d->labelsize(description_font_size);
  tofile_d2->labelsize(description_font_size);
  Fl_Button *createpdf = new Fl_Button(50,visina_programa-100,sirina_programa-100,50,"Create PDF");
  createpdf->callback(createPDF);

  setDefaults();

  viewport->end();
  window->size_range(300,300);
  window->resizable(viewport);
  window->end();
  window->show(argc, argv);
  return Fl::run();
}
