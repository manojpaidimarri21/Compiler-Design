

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
        ans=ans+(s[i]-'A')*p;
      }
      p=p*16;
  }

  return ans;
}

map<string, string> optab;
map<string, int> symtab;


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

void optab_insert(string str1,string str2)
{
  optab.insert(pair<string,string>(str1,str2));
}


void symtab_insert(string str,int locctr)
{
  symtab.insert(pair<string,int>(str,locctr));
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
   return s;
}

string set_width(string s,int a)
{
  int n=s.length();
  string p=s;
  for(int i=0;i<(a-n);i++)
  {
    p="0"+p;
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


// --------------pass1----------------------------------------//


  getline(input_file,input_line);
  divide_line(input_line,divided_input_line);
  set_divided_line_input(divided_input_line);
  int locctr=0,str_addr=0;
  if(divided_input_line[1] == "START")
  {
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
          std::cout << "ERROR: DUPLICATE SYMBOLS PRESENT" << '\n';
        //  cout<<divided_input_line[0]<<endl;
        }
        else
        {
          symtab_insert(divided_input_line[0],locctr);
      //    cout<<divided_input_line[0]<<endl;


        }


      }

      if(optab_search(divided_input_line[1]))
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
      else
      {
         cout<<"ERROR:INVALID OPERATION CODE"<<endl;
         cout<<divided_input_line[1]<<endl;

      }

    }
    else
    {
      intern_file<<"    "<<input_line<<endl;
    }
    getline(input_file,input_line);
    divide_line(input_line,divided_input_line);
    set_divided_line_input(divided_input_line);


  }
/*  cout<<endl;
  map<string, int>::iterator itr;

  for (itr = symtab.begin(); itr != symtab.end(); ++itr) {
      cout<<itr->first<<endl;
    }*/
  intern_file<<"        "<<input_line<<endl;
  int program_length=locctr-str_addr;
  intern_file<<"length = "<<program_length;

  input_file.close();
  intern_file.close();
//-------pass 2--------------------------------//

ofstream list_file("listing.txt");
ifstream intern_file1("intermediate.txt");


getline(intern_file1,input_line);
divide_line(input_line,divided_input_line);
set_divided_line_intermidiate(divided_input_line);
//  cout<<divided_input_line[1]<<endl;
string file_name=divided_input_line[1];
int t=divided_input_line[1].size();
while(t<6)
{
 file_name=file_name+" ";
 t++;
}
list_file<<"H"<<file_name<<set_width(divided_input_line[0],6)<<set_width(int_to_str_hex(program_length),6)<<endl;

if(divided_input_line[1]=="START")
{
 //write listting line
 getline(intern_file1,input_line);
 divide_line(input_line,divided_input_line);
 set_divided_line_intermidiate(divided_input_line);

}


string txt_record="T";
string txt_record_str_addr=set_width(divided_input_line[0],6);
string txt_record_obj_code="";
//locctr-0 lbl-1 opc-2 opd-3
string opd_addr;
bool RESB_RESW_occured=false;
while (divided_input_line[2]!="END") {
 string temp="";
 if(input_line.size()>4 && input_line[4]!='.')
 {
   if(RESB_RESW_occured && divided_input_line[2]!="RESB" && divided_input_line[2]!="RESW")
   {
     txt_record_str_addr=set_width(divided_input_line[0],6);
   //  cout<<divided_input_line[0]<<endl;
     RESB_RESW_occured=false;
   }


   if(optab_search(divided_input_line[2]))
   {

     if(divided_input_line[3]!="        ")
     {
       string s="";
       string last_2_of_opd="";
       int n=divided_input_line[3].size();
       for(int k=0;k<n-1;k++)
       {
         s=s+divided_input_line[3][k];
       }
       if(n>=3) last_2_of_opd=last_2_of_opd+divided_input_line[3][n-3]+divided_input_line[3][n-2];


       if(last_2_of_opd==",X")
       {
         string h="";
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
           opd_addr="0";
           std::cout << "ERROR:UNDEFINED SYMBOL" <<endl;

         }

         opd_addr[0]='9';
       }
       else
       {
         if(symtab_search(s))
         {
           opd_addr=int_to_str_hex(symtab[s]);
         }
         else
         {
           opd_addr="0";
           std::cout << "ERROR:UNDEFINED SYMBOL" <<endl;
         //  cout<<s<<endl;
         }
       }

     }
     else
     {
       opd_addr="0";
     }
     //assemble
     temp=remove_last_character(optab[divided_input_line[2]])+set_width(opd_addr,4);
   //  if(divided_input_line[2]=="RSUB") cout<<temp<<endl;
   }
   else if(divided_input_line[2]=="WORD" )
   {
      int p=stoi(divided_input_line[3]);
      string q=int_to_str_hex(p);
       temp =set_width(q,6);
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


list_file<<"E00"<<int_to_str_hex(str_addr)<<endl;

list_file.close();
intern_file1.close();


}



/*int n=divided_input_line.size();
 cout<<n<<endl;
for(int i=0;i<n;i++)
{
  cout<<divided_input_line[i]<<endl;
}*/
