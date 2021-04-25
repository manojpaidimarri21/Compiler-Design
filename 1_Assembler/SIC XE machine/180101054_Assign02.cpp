

//my program should be compiled and executed in LINUX g++

// one Assumption is that label and opcode,operand are seperated by spaces.

//listing.txt is the output object program_length
//optab.txt is the opcodes that are used
//input.txt is the input code
#include <bits/stdc++.h>
using namespace std;


void divide_line(string str,vector<string> &divided_input_line)
{
  divided_input_line.clear();
  int n=str.length();
  string word="";
  for(int i=0;i<n;i++)
  {
    if(str[i]==' ')
    {
      if(word!="")
      {
        divided_input_line.push_back(word);
        word="";
      }
    }
    else
    {
      word=word+str[i];
    }
  }
  if(word!="")
  {
    divided_input_line.push_back(word);
    word="";
  }

}
void set_divided_line_input(vector<string> &divided_input_line)
{
  int n=divided_input_line.size();
  if(n==2)
  {
    auto it = divided_input_line.insert(divided_input_line.begin(),"        ");
  }
  else if(n==1)
  {
    auto it = divided_input_line.insert(divided_input_line.begin(),"        ");
    divided_input_line.push_back("        ");
    string s="";
    int n=divided_input_line[1].size();
    for(int i=0;i<n-1;i++)
    {
      s=s+divided_input_line[1][i];
    }
    divided_input_line[1]=s;
  }
}

void set_divided_line_intermidiate(vector<string> &divided_input_line)
{
  int n=divided_input_line.size();
  if(n==3)
  {
    auto it = divided_input_line.insert(divided_input_line.begin()+1,"        ");

  }
  else if(n==2 && divided_input_line[0]!="END")
  {
    auto it = divided_input_line.insert(divided_input_line.begin()+1,"        ");
    divided_input_line.push_back("        ");
    string s="";
    int n=divided_input_line[2].size();
    for(int i=0;i<n-1;i++)
    {
      s=s+divided_input_line[2][i];
    }
    divided_input_line[2]=s;
  }
  else if(n==2)
  {
    auto it = divided_input_line.insert(divided_input_line.begin(),"        ");
    auto ti = divided_input_line.insert(divided_input_line.begin(),"        ");

  }
}


int hex_str_to_int(string s)
{
  int n=s.length();
  int p=1;
  int ans=0;
  for(int i=n-2;i>=0;i--)
  {
      if(s[i]>='0' && s[i]<='9')
      {
        ans=ans+(s[i]-'0')*p;
      }
      else
      {
        ans=ans+(s[i]-'A')*p+10*p;
      }
      p=p*16;
  }

  return ans;
}
int hex_str_to_int_1(string s)
{
  int n=s.length();
  int p=1;
  int ans=0;
  for(int i=n-1;i>=0;i--)
  {
      if(s[i]>='0' && s[i]<='9')
      {
        ans=ans+(s[i]-'0')*p;
        p=p*16;
      }
      else if(s[i]>='A' && s[i]<='F')
      {
        ans=ans+(s[i]-'A')*p+10*p;
        p=p*16;
      }

  }

  return ans;
}




string int_to_str_bin(int n)
{
    // array to store binary number
    string str="";

    // counter for binary array
    int i = 0;
    while (n > 0) {
        if(n%2==0)
        str="0"+str;
        else
        str="1"+str;
        n = n / 2;
    }

    return str;
}

struct literalDetails{
  string val;
  int length;
  int address;
};
map<string, string> optab;
map<string, int> symtab;
map<string, literalDetails> littab;
map<string, string> symtab2;
map<string, vector<string> > extdeftab;
map<string, vector<string> > extreftab;
map<string, int> sect_length;



bool optab_search(string str)
{
  map<string, string>::iterator itr;
  for (itr = optab.begin(); itr != optab.end(); ++itr) {
        if(itr->first==str)
        {
          return 1;
        }
    }
}

bool symtab_search(string str)
{
  map<string, int>::iterator itr;
  for (itr = symtab.begin(); itr != symtab.end(); ++itr) {
        if(itr->first==str)
        {
          return 1;
        }
    }
}

bool littab_search(string str)
{
  map<string, literalDetails>::iterator itr;
  for (itr = littab.begin(); itr != littab.end(); ++itr) {
        if( (itr->second).val==str && (itr->second).address==-1 )
        {
          return 1;
        }
    }
}

void optab_insert(string str1,string str2)
{
  optab.insert(pair<string,string>(str1,str2));
}


void symtab_insert(string str,int locctr)
{
  symtab.insert(pair<string,int>(str,locctr));
}


void littab_insert(string str,literalDetails ld)
{
  littab.insert(pair<string,literalDetails>(str,ld));
}



string int_to_str_hex(int val)
{
   string s="";

   while(val>0)
   {
     int r=val%16;
     val/=16;
     if(r>=0 && r<=9)
     {
       char c='0'+r;
       s=c+s;
     }
     else
     {
       char c='A'+(r-10);
       s=c+s;
     }
   }
   int n=s.size();
   while(n<4)
   {
     s="0"+s;
     n++;
   }


   return s;
}

string set_width(string s,int a)
{
  int n=s.length();
  string p=s;
  if(n>a)
  {
    p="";
    for(int i=n-1;i>=(n-a);i--)
    {
      p=s[i]+p;
    }
  }
  for(int i=0;i<(a-n);i++)
  {
    p="0"+p;
  }

  return p;
}
string set_width_back(string s,int a)
{
  int n=s.length();
  string p=s;
  for(int i=0;i<(a-n);i++)
  {
    p=p+" ";
  }
  return p;
}

string remove_last_character(string str)
{
  string p="";
  int n=str.size();
  for(int i=0;i<n-1;i++)
  {
    p=p+str[i];
  }
  return p;

}
void set_vector_comma_seperated(vector<string> &v,string str)
{
  v.clear();
  int n=str.length();
  string word="";
  for(int i=0;i<n;i++)
  {
    if(str[i]==',')
    {
      if(word!="")
      {
        v.push_back(word);
        word="";
      }
    }
    else
    {
      word=word+str[i];
    }
  }
  if(word!="")
  {
    v.push_back(word);
    word="";
  }
}


string combiner(string opcode,string nixbpe)
{
  string s="";
//  cout<<"opcode 1 "<<endl;
//  cout<<opcode<<endl;

  if(opcode.size()==2)
  {
    opcode=opcode+"0";
  }
  int a=hex_str_to_int(opcode);
//  cout<<"opcode 2 "<<endl;
//  cout<<opcode<<endl;
//  cout<<"a "<<a<<endl;
  string opcode_bin=int_to_str_bin(a);
  opcode_bin=set_width(opcode_bin,8);
  for(int i=0;i<6;i++)
  {
    s=s+opcode_bin[i];
  }
  //cout<<s<<endl;
  s=s+nixbpe;
//  cout<<s<<endl;
  string ans="";
  string temp="";
  temp=int_to_str_hex((s[0]-'0')*8+(s[1]-'0')*4+(s[2]-'0')*2+(s[3]-'0'));
  ans=ans+temp[3];
  temp=int_to_str_hex((s[4]-'0')*8+(s[5]-'0')*4+(s[6]-'0')*2+(s[7]-'0'));
  ans=ans+temp[3];
  temp=int_to_str_hex((s[8]-'0')*8+(s[9]-'0')*4+(s[10]-'0')*2+(s[11]-'0'));
  ans=ans+temp[3];

  return ans;

}


int main() {


  ifstream input_file("input.txt");
  ofstream intern_file("intermediate.txt");
  ifstream optab_file("optab.txt");
  string input_line;
  vector<string> divided_input_line;


  while( getline(optab_file,input_line) )
  {
    divide_line(input_line,divided_input_line);
    optab_insert(divided_input_line[0],divided_input_line[1]);
  }
  optab_file.close();
symtab_insert("A",0);
symtab_insert("X",1);
symtab_insert("L",2);
symtab_insert("B",3);
symtab_insert("S",4);
symtab_insert("T",5);
symtab_insert("F",6);
symtab_insert("PC",8);
symtab_insert("SW",9);


// --------------pass1----------------------------------------//

  string sectName="        ";
  getline(input_file,input_line);
  divide_line(input_line,divided_input_line);
  set_divided_line_input(divided_input_line);
  int locctr=0,str_addr=0;
  if(divided_input_line[1] == "START")
  {
    sectName=divided_input_line[0];
    str_addr=hex_str_to_int(divided_input_line[2]);
    locctr=str_addr;
    intern_file<<int_to_str_hex(locctr)<<"    "<<input_line<<endl;
    getline(input_file,input_line);
    divide_line(input_line,divided_input_line);
    set_divided_line_input(divided_input_line);

  }
  else
  {
    locctr=0;
  }


  while(divided_input_line[1]!="END")
  {
    if(input_line[0]!='.')
    {
      intern_file<<int_to_str_hex(locctr)<<"    "<<input_line<<endl;
      if(divided_input_line[0]!="        ")
      {


        if(symtab_search(divided_input_line[0]))
        {
        //  std::cout << "ERROR: DUPLICATE SYMBOLS PRESENT" << '\n';
        //  cout<<divided_input_line[0]<<endl;
          symtab[divided_input_line[0]]=locctr;
        }
        else
        {
          symtab_insert(divided_input_line[0],locctr);
      //    cout<<divided_input_line[0]<<endl;
      //    cout<<locctr<<endl;


        }


      }


      if(divided_input_line[2][0]=='=')
      {

        bool p=littab_search(divided_input_line[2]);
        if(!p)
        {
          struct literalDetails ld={divided_input_line[2],divided_input_line[2].size()-1,-1};
          littab_insert(divided_input_line[0],ld);
        }

      }


        if(divided_input_line[1][0]=='+')
        {
          //cout<<divided_input_line[1]<<endl;
          locctr=locctr+4;
        }
        else if(divided_input_line[1]=="EXTDEF")
        {
          std::vector<string> v;
      //    cout<<"ENTERED"<<endl;
      //    cout<<sectName<<"  "<<remove_last_character(divided_input_line[2])<<endl;
          set_vector_comma_seperated(v,remove_last_character(divided_input_line[2]));

            extdeftab.insert(pair<string,vector<string>>(sectName,v) );

          /*  std::vector<string> test;
            test=extdeftab[sectName];
            for(int z=0;z<test.size();z++)
            {
              cout<<"test  "<<test[z]<<endl;
            }*/

        }
        else if(divided_input_line[1]=="EXTREF")
        {
          std::vector<string> v;
          set_vector_comma_seperated(v,remove_last_character(divided_input_line[2]));
          extreftab.insert(pair<string,vector<string>>(sectName,v) );
        }
        else if(divided_input_line[1]=="CLEAR" || divided_input_line[1]=="COMPR" || divided_input_line[1]=="TIXR")
        {
          locctr=locctr+2;
        }
        else if(optab_search(divided_input_line[1]))
        {
          locctr=locctr+3;
        }
        else if(divided_input_line[1]=="WORD")
        {
          locctr=locctr+3;
        }
        else if(divided_input_line[1]== "RESW")
        {
          locctr=locctr+3*hex_str_to_int(divided_input_line[2]);
        }
        else if(divided_input_line[1]=="RESB")
        {
          locctr=locctr+stoi(divided_input_line[2]);
        }
        else if(divided_input_line[1]=="BYTE")
        {
          if(divided_input_line[2][0]=='X')
          {
            locctr=locctr+(divided_input_line[2].length()-4)/2;
          }
          else if(divided_input_line[2][0]=='C')
          {
            locctr=locctr+(divided_input_line[2].length()-4);

          }
        }
        else if(divided_input_line[1]=="BYTE")
        {
          locctr=locctr+4;
        }
        else if(remove_last_character(divided_input_line[2])=="CSECT")
        {

          sect_length.insert(pair<string,int>(sectName,locctr));
      //    cout<<"SECT FOUND "<<sectName<<endl;
      //    cout<<locctr<<endl;


          locctr=0;

          sectName=divided_input_line[1];
        }
        else if(divided_input_line[1]=="LTORG")
        {
          map<string, literalDetails>::iterator itr;
           for (itr = littab.begin(); itr != littab.end(); ++itr) {
             if((itr->second).address==-1)
             {

               (itr->second).address=locctr;
               intern_file<<int_to_str_hex(locctr)<<"    *      "<<(itr->second).val<<endl;
               locctr=locctr+3;
             }


             }

        }
        else if(divided_input_line[1]=="EQU")
        {
            if(remove_last_character(divided_input_line[2])=="*")
            {
              divided_input_line[2]=int_to_str_hex(locctr);
            }
            symtab2.insert(pair<string,string>(divided_input_line[0],divided_input_line[2]));
        }
        else
        {
        //   cout<<"ERROR:INVALID OPERATION CODE"<<endl;
        //   cout<<divided_input_line[1]<<endl;

        }


    }



    getline(input_file,input_line);
    divide_line(input_line,divided_input_line);
    set_divided_line_input(divided_input_line);
   if(divided_input_line[1]=="END")
   {
     sect_length.insert(pair<string,int>(sectName,locctr));

   }

  }



/*  cout<<endl;
  map<string, int>::iterator itr;

  for (itr = symtab.begin(); itr != symtab.end(); ++itr) {
      cout<<itr->first<<endl;
    }*/

  /*  map<string, literalDetails>::iterator itr;
    for (itr = littab.begin(); itr != littab.end(); ++itr) {
        cout<<" *1* "<<itr->first<<endl;
        cout<<" *2* "<<(itr->second).val<<endl;
        cout<<" *3* "<<(itr->second).length<<" *4* "<<(itr->second).address<<endl;
      }*/



      intern_file<<"        "<<input_line<<endl;

    if(divided_input_line[1]=="END")
    {
       map<string, literalDetails>::iterator itr;
       for (itr = littab.begin(); itr != littab.end(); ++itr) {
         if((itr->second).address==-1)
         {

           (itr->second).address=locctr;
           intern_file<<int_to_str_hex(locctr)<<"    *      "<<(itr->second).val<<endl;
           locctr=locctr+3;
         }


         }
    }
  int program_length=locctr-str_addr;
  intern_file<<"length = "<<program_length;

  input_file.close();
  intern_file.close();




//------------------------pass 2-----------------------------------------//






  ofstream list_file("listing.txt");
  ifstream intern_file1("intermediate.txt");


  getline(intern_file1,input_line);
  divide_line(input_line,divided_input_line);
  set_divided_line_intermidiate(divided_input_line);
  int present_sect_number=0;
  do{
    string file_name="";
    string present_sect_name="";
    present_sect_number++;
    if(divided_input_line[2]=="START"){
         file_name=divided_input_line[1];
      }
      else
      {
         file_name=divided_input_line[2];
      }
      present_sect_name=file_name;
      int t=file_name.size();
      while(t<6)
      {
       file_name=file_name+" ";
       t++;
      }
      std::vector<string> modification_records;
      if(present_sect_name=="WRREC")
      list_file<<"H"<<file_name<<"000000"<<set_width(int_to_str_hex(sect_length[present_sect_name]+1),6)<<endl;
      else
        list_file<<"H"<<file_name<<"000000"<<set_width(int_to_str_hex(sect_length[present_sect_name]),6)<<endl;

        if(remove_last_character(divided_input_line[3])=="CSECT")
        {
         //write listting line
         getline(intern_file1,input_line);
         divide_line(input_line,divided_input_line);
         set_divided_line_intermidiate(divided_input_line);
        }

//--------------define and refer record--------//



         string def_record_code="";
         int sect_length=extdeftab[present_sect_name].size();
      //   cout<<file_name<<sect_length<<endl;
          for(int i=0;i<sect_length;i++)
          {


            def_record_code=def_record_code+set_width_back(extdeftab[present_sect_name][i],6);
            string h=extdeftab[present_sect_name][i];
            if(symtab_search(h))
            {
              def_record_code=def_record_code+set_width(int_to_str_hex(symtab[h]),6);
            }
            else
            {
              def_record_code=def_record_code+"0000000";
            }
          }
          int def_record_size=def_record_code.size();
          string temp="";
          for(int i=0;i<def_record_size;i++)
          {
            if(i>0 && i%73==0)
            {
              list_file<<"D"<<temp<<endl;

             temp="";
            }
            else
            {
              temp=temp+def_record_code[i];
            }
          }

          if(temp!="")
          {
            list_file<<"D"<<temp<<endl;
          }



          string ref_record_code="";
          sect_length=extreftab[present_sect_name].size();
      //    cout<<present_sect_name<<" "<<sect_length<<endl;
           for(int i=0;i<sect_length;i++)
           {
             ref_record_code=ref_record_code+set_width_back(extreftab[present_sect_name][i],6);
       //      cout<<file_name<<" "<<extdeftab[file_name][i];
           }
           int ref_record_size=ref_record_code.size();
            temp="";
           for(int i=0;i<ref_record_size;i++)
           {
             if(i>0 && i%73==0)
             {
               list_file<<"R"<<temp<<endl;

              temp="";
             }
             else
             {
               temp=temp+ref_record_code[i];
             }
           }

           if(temp!="")
           {
             list_file<<"R"<<temp<<endl;
           }

















//-----------------------------------------------------//




        string txt_record="T";
        string txt_record_str_addr=set_width(divided_input_line[0],6);
        string txt_record_obj_code="";
        //locctr-0 lbl-1 opc-2 opd-3
        string opd_addr;
        bool RESB_RESW_occured=false;

        while (divided_input_line[0]!="length" && remove_last_character(divided_input_line[3])!="CSECT") {
         string temp="";
         string nixbpe="";
         if(input_line.size()>4 && input_line[4]!='.')
         {
           if(RESB_RESW_occured && divided_input_line[2]!="RESB" && divided_input_line[2]!="RESW")
           {
             txt_record_str_addr=set_width(divided_input_line[0],6);
             RESB_RESW_occured=false;
           }


           if(optab_search(divided_input_line[2])||(divided_input_line[2].size()>0 && divided_input_line[2][0]=='+'))
           {


               string s="";
               string last_2_of_opd="";
               int n=divided_input_line[3].size();
               for(int k=0;k<n-1;k++)
               {
                 s=s+divided_input_line[3][k];
               }
               if(n>=3) last_2_of_opd=last_2_of_opd+divided_input_line[3][n-3]+divided_input_line[3][n-2];



               if(divided_input_line[2]=="COMPR")
               {
                 string reg1="";
                 string reg2="";
                 reg1+=divided_input_line[3][0];
                 reg2+=divided_input_line[3][2];
                 temp=temp+remove_last_character(optab[divided_input_line[2]])+set_width(int_to_str_hex(symtab[reg1]),1)+set_width(int_to_str_hex(symtab[reg2]),1);

               }
               else if(divided_input_line[2]=="CLEAR"||divided_input_line[2]=="TIXR")
               {
                 string reg1="";
                 reg1+=divided_input_line[3][0];
                 temp=temp+remove_last_character(optab[divided_input_line[2]])+set_width(int_to_str_hex(symtab[reg1]),1)+"0";

               }
               else
               {
                     if(divided_input_line[3][0]=='#')
                     {
                  //     cout<<"hi"<<endl;
                       string k=remove_last_character(divided_input_line[3]);
                       int r=k.length();
                      // cout<<"k "<<k<<endl;
                    //   cout<<"r "<<r<<endl;
                       string k1="";
                       for(int i=1;i<r;i++)
                       {
                         k1=k1+k[i];
                       }
                       int number=hex_str_to_int_1(k1);
                       //cout<<"k1 "<<k1<<endl;
                      // cout<<"number "<<number<<endl;
                       if(number>=0 && number<=4095)
                       {
                         temp=combiner(remove_last_character(optab[divided_input_line[2]]),"010000")+set_width(int_to_str_hex(number),3);
                       }
                       else
                       {
                         //
                       }
                     }
                     else if(divided_input_line[2][0]=='+')
                     {
                    //   cout<<"entered"<<endl;
                       int l1=divided_input_line[2].size();
                       string k1="";
                       for(int i=1;i<l1;i++)
                       {
                         k1=k1+divided_input_line[2][i];
                       }
                       nixbpe="110001";
                        string h="";
                       if(last_2_of_opd==",X")
                       {

                         for(int k=0;k<n-3;k++)
                         {
                           h=h+divided_input_line[3][k];
                         }
                         if(symtab_search(h))
                         {
                           opd_addr=int_to_str_hex(symtab[h]+32768);
                         }
                         else
                         {
                           opd_addr="0000";
                        //   std::cout << "ERROR:UNDEFINED SYMBOL" <<endl;
                         }
                        nixbpe="111001";



                       }
                       if(h=="")
                       {
                         h=remove_last_character(divided_input_line[3]);
                       }

                         sect_length=extreftab[present_sect_name].size();
                         //cout<<present_sect_name<<" "<<sect_length<<endl;
                          for(int i=0;i<sect_length;i++)
                          {
                            if(extreftab[present_sect_name][i]==h)
                            {
                              string add_to_modification_records="";
                              add_to_modification_records="M"+set_width(int_to_str_hex(hex_str_to_int_1(divided_input_line[0])+1),6)+"05+"+h;
                              modification_records.push_back(add_to_modification_records);
                            }
                      //      cout<<file_name<<" "<<extdeftab[file_name][i];
                          }

                    //   cout<<"optab[k1]"<<endl;
                    //   cout<<optab[k1]<<endl;

                       temp=combiner(optab[k1],nixbpe)+"00000";

                     }
                    else if(divided_input_line[3][0]=='@')
                    {
                    //  cout<<"entered"<<endl;
                      string k=remove_last_character(divided_input_line[3]);
                      int r=k.length();
                     // cout<<"k "<<k<<endl;
                   //   cout<<"r "<<r<<endl;
                      string k1="";
                      for(int i=1;i<r;i++)
                      {
                        k1=k1+k[i];
                      }
                      s=k1;
                      if(symtab_search(s))
                      {
                        int t=hex_str_to_int_1(divided_input_line[0]);

                        opd_addr=int_to_str_hex(symtab[s]-t-3);
                        temp=combiner(remove_last_character(optab[divided_input_line[2]]),"100010")+set_width(opd_addr,3);

                      }
                    }
                    else if(divided_input_line[3][0]=='=')
                    {
                      int t;

                        t=hex_str_to_int_1(divided_input_line[0]);
                        int litaddress=0;

                        map<string, literalDetails>::iterator itr;
                        for (itr = littab.begin(); itr != littab.end(); ++itr) {
                              if( (itr->second).val==divided_input_line[3] )
                              {
                                litaddress=(itr->second).address;
                              }
                          }


                        opd_addr=int_to_str_hex(litaddress-t-3);



                      temp=combiner(remove_last_character(optab[divided_input_line[2]]),"110010")+set_width(opd_addr,3);



                    }
                    else if(divided_input_line[2]=="RSUB"||remove_last_character(divided_input_line[2])=="RSUB")
                    {
                      temp="4F0000";
                    }
                     else if(symtab_search(s))
                     {
                       int t;

                         t=hex_str_to_int_1(divided_input_line[0]);
                       if(symtab[s]<=(t+3))
                       {
                         opd_addr=int_to_str_hex(symtab[s]-t-3+4096);

                       }
                       else
                       {
                         opd_addr=int_to_str_hex(symtab[s]-t-3);

                       }
                       string h=s;
                       sect_length=extreftab[present_sect_name].size();
                       //cout<<present_sect_name<<" "<<sect_length<<endl;
                        for(int i=0;i<sect_length;i++)
                        {
                          if(extreftab[present_sect_name][i]==h)
                          {
                            string add_to_modification_records="";
                            add_to_modification_records="M"+set_width(int_to_str_hex(hex_str_to_int_1(divided_input_line[0])+1),6)+"05+"+h;
                            modification_records.push_back(add_to_modification_records);
                          }
                    //      cout<<file_name<<" "<<extdeftab[file_name][i];
                        }

                       temp=combiner(remove_last_character(optab[divided_input_line[2]]),"110010")+set_width(opd_addr,3);

                     }

                     else
                     {
                       opd_addr="0000";
                    //   std::cout << "ERROR:UNDEFINED SYMBOL" <<endl;
                  //     cout<<s<<endl;
                //       cout<<divided_input_line[2]<<endl;
                     }


               }



         }
         else if(divided_input_line[2][0]=='*')
         {
        //   cout<<"hi"<<" * "<<endl;
           if(divided_input_line[3][0]=='=')
           {
             if(divided_input_line[3][1]=='X')
             {
               for(int i=3;i<5;i++)
               temp=temp+divided_input_line[3][i];
             }
             else if(divided_input_line[3][1]=='C')
             {

               for(int i=3;i<divided_input_line[3].size()-2;i++)
               {
                 int p=divided_input_line[3][i];
                 temp=temp+set_width(int_to_str_hex(p),2);
                // cout<<divided_input_line[3][i]<<" ";
               }
            //   cout<<endl;
              // cout<<temp<<endl;
             }

           }

         }


       else if(divided_input_line[2]=="WORD" )
       {
         bool q=true;
         int z=divided_input_line[3].size();
         string a[2];
         a[0]="";
         a[1]="";
         int pi=0;
         for(int k=0;k<z-1;k++)
         {
           if(divided_input_line[3][k]=='-')
           {
             q=false;
             pi++;
           }
           else
           {
             a[pi]=a[pi]+divided_input_line[3][k];

           }
         }

         sect_length=extreftab[present_sect_name].size();
         //cout<<present_sect_name<<" "<<sect_length<<endl;
          for(int i=0;i<sect_length;i++)
          {
            if(extreftab[present_sect_name][i]==a[0])
            {
              string add_to_modification_records="";
              add_to_modification_records="M"+set_width(int_to_str_hex(hex_str_to_int_1(divided_input_line[0])),6)+"06+"+a[0];
              modification_records.push_back(add_to_modification_records);
            }
      //      cout<<file_name<<" "<<extdeftab[file_name][i];
          }

           for(int i=0;i<sect_length;i++)
           {
             if(extreftab[present_sect_name][i]==a[1])
             {
               string add_to_modification_records="";
               add_to_modification_records="M"+set_width(int_to_str_hex(hex_str_to_int_1(divided_input_line[0])),6)+"06-"+a[1];
               modification_records.push_back(add_to_modification_records);
             }
       //      cout<<file_name<<" "<<extdeftab[file_name][i];
           }

          if(q==true){
            int p=stoi(divided_input_line[3]);
            string q=int_to_str_hex(p);
            temp =set_width(q,6);
          }
          else
          {
            temp="000000";
          }


       }
       else if(divided_input_line[2]=="BYTE")
       {
         if(divided_input_line[3][0]=='X')
         {
           for(int i=2;i<4;i++)
           temp=temp+divided_input_line[3][i];
         }
         else if(divided_input_line[3][0]=='C')
         {

           for(int i=2;i<divided_input_line[3].size()-2;i++)
           {
             int p=divided_input_line[3][i];
             temp=temp+int_to_str_hex(p);

           }
           //cout<<temp<<endl;
         }
       }

           int z=temp.size();
        //   cout<<input_line<<endl;
        //   cout<<divided_input_line[2]<<endl;
        //   cout<<temp<<endl;

           if((temp.size()+txt_record_obj_code.size()>60) && txt_record_obj_code.size()>0)
           {
             txt_record=txt_record+txt_record_str_addr+set_width(int_to_str_hex(txt_record_obj_code.size()/2),2)+txt_record_obj_code;
             list_file<<txt_record<<endl;
             txt_record="T";
             txt_record_str_addr=set_width(divided_input_line[0],6);
             txt_record_obj_code=temp;
             //locctr-0 lbl-1 opc-2 opd-3
           }
           else
           {
             txt_record_obj_code=txt_record_obj_code+temp;
           }
         }

         getline(intern_file1,input_line);
         divide_line(input_line,divided_input_line);
         set_divided_line_intermidiate(divided_input_line);


         if(divided_input_line[2]=="RESB"|| divided_input_line[2]=="RESW")
         {
           RESB_RESW_occured=true;
           if(txt_record_obj_code!="")
           {
             txt_record=txt_record+txt_record_str_addr+set_width(int_to_str_hex(txt_record_obj_code.size()/2),2)+txt_record_obj_code;
             list_file<<txt_record<<endl;
             txt_record="T";
             txt_record_obj_code="";

           }
         }



        }

        if(txt_record_obj_code!="")
        {  txt_record=txt_record+txt_record_str_addr+set_width(int_to_str_hex(txt_record_obj_code.size()/2),2)+txt_record_obj_code;
        list_file<<txt_record<<endl;
        }

        for(int i=0;i<modification_records.size();i++)
        {
          list_file<<modification_records[i]<<endl;

        }
        if(present_sect_number==1)
        list_file<<"E00"<<int_to_str_hex(str_addr)<<endl;
        else
        list_file<<"E"<<endl;


  }
  while (remove_last_character(divided_input_line[3])=="CSECT");

  list_file.close();
  intern_file1.close();

}
