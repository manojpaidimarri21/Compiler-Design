

//command to compile : g++ linking_loader.cpp
//command to run : ./a.out
// progaddr should be given as input

//In our text book case it is 4000

//memory contents are displayed in output.txt




#include <bits/stdc++.h>
using namespace std;



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



int hex_str_to_int(string s)
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
    //  cout<<ans<<endl;

  }

  return ans;
}

string add_two_hex_strings(string str1,string str2)
{
  int a=hex_str_to_int(str1);
  int b=hex_str_to_int(str2);
  return int_to_str_hex(a+b);
}


int bin_to_int(string n)
{
    string num = n;
    int dec_value = 0;

    int base = 1;

    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
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

    int k=str.size();
    while(k<8)
    {
      str="0"+str;
      k++;
    }
    return str;
}

string combiner(string str1)
{
  string first="";
  first+=str1[0];
  string second ="";
  second+=str1[1];
  return int_to_str_bin((hex_str_to_int(first)*16)+(hex_str_to_int(second)));
}

string bin_to_hex(string s)
{
  int k=(s[0]-'0')*8+(s[1]-'0')*4+(s[2]-'0')*2+(s[3]-'0');
  if(k==0)
  {
    return "0";
  }
  string t=int_to_str_hex(k);

  return t;
}


string add_two_binary_numbers(string a, string b)
{
    string result = "";
    int s = 0;
    int i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0 || s == 1)
    {
        s += ((i >= 0)? a[i] - '0': 0);
        s += ((j >= 0)? b[j] - '0': 0);

        result = char(s % 2 + '0') + result;

        s /= 2;

        i--; j--;
    }
    return result;
}

char flip(char c) {return (c == '0')? '1': '0';}

string twos_complement(string bin)
{
    int n = bin.length();
    int i;

    string ones, twos;
    ones = twos = "";

    for (i = 0; i < n; i++)
        ones += flip(bin[i]);

    twos = ones;
    for (i = n - 1; i >= 0; i--)
    {
        if (ones[i] == '1')
            twos[i] = '0';
        else
        {
            twos[i] = '1';
            break;
        }
    }


    if (i == -1)
        twos = '1' + twos;

    return twos;
}

string hex_str_to_bin(string str)
{
  string t = int_to_str_bin(hex_str_to_int(str));

  return t;
}

string sub_two_bin(string str1,string str2)
{
  int a=bin_to_int(str1);
  int b=bin_to_int(str2);

  return int_to_str_bin(a-b);

}

int main() {


      map< pair<string,string> , pair<string,string> > estab ;

      map<string,string> memory;

    //------------------  Pass 1   ------------------------------------//

      ifstream input_file_pass1("input.txt");
      ofstream estab_file("estab.txt");
      string input_line="";
      string csaddr="";
      string progaddr="";

      cin>>progaddr;

      csaddr=progaddr;
      string present_csect_name="";
      string cslth="";
      getline(input_file_pass1,input_line);
      while (input_line.length()==0 )
        getline(input_file_pass1,input_line);

      while(input_line!="END")
      {
        if(input_line[0]=='H')
        {
          present_csect_name  =input_line.substr(1,6);
          cslth=input_line.substr(13,6);

          bool p=false;
          map< pair<string,string> , pair<string,string> > ::iterator itr;
          for (itr = estab.begin(); itr != estab.end(); ++itr) {
                if( (itr->first).first == present_csect_name && (itr->first).second== "      " )
                {
                  p=true;
                  cout<<"DUPLICATE  EXTERNAL SYMBOLS"<<endl;
                }
            }

            if(p==false)
            {
              estab.insert(pair<pair<string,string>,pair<string,string>>({present_csect_name,"      "},{progaddr,cslth}));
              estab_file<<present_csect_name<<" "<<"       "<<csaddr<<" "<<cslth<<endl;
            }



        }

        while(input_line[0]!='E')
        {
        getline(input_file_pass1,input_line);
        while (input_line.length()==0 )
          getline(input_file_pass1,input_line);

          if(input_line[0]=='D')
            {
              int no_of_symbols=input_line.length()/12 ;
              for(int i=0;i<no_of_symbols;i++)
              {

                string symbol=input_line.substr(1+i*12,6);
                string address=input_line.substr(7+i*12,6);
                bool p=false;
                map< pair<string,string> , pair<string,string> > ::iterator itr;
                for (itr = estab.begin(); itr != estab.end(); ++itr) {
                      if( (itr->first).first == "      " && (itr->first).second== symbol )
                      {
                        p=true;
                        cout<<"DUPLICATE  EXTERNAL SYMBOLS"<<endl;
                      }
                  }

                  if(p==false)
                  {
                    estab.insert(pair<pair<string,string>,pair<string,string>>({"      ",symbol},{add_two_hex_strings(csaddr,address),"      "}));
                    estab_file<<"      "<<" "<<symbol<<" "<<add_two_hex_strings(csaddr,address)<<"      "<<endl;
                  }

              }
            }


          }
          csaddr=add_two_hex_strings(csaddr,cslth);


          getline(input_file_pass1,input_line);
          while (input_line.length()==0 )
            getline(input_file_pass1,input_line);



      }


      input_file_pass1.close();
      estab_file.close();

    //-------------------- Pass 2--------------------------------------//

    string execaddr="";
    csaddr=progaddr;
    execaddr=progaddr;
    input_line="";
    ifstream input_file_pass2("input.txt");

    vector<string> modification_addresses;
    vector<int> modification_length;
    vector<string> modification_type;
    vector<string> modification_opd_address;



    getline(input_file_pass2,input_line);
    while (input_line.length()==0 )
      getline(input_file_pass2,input_line);

    while(input_line!="END")
    {

      if(input_line[0]=='H')
      {
        cslth=input_line.substr(13,6);
      }

      while(input_line[0]!='E')
      {
        getline(input_file_pass2,input_line);
        while (input_line.length()==0 )
          getline(input_file_pass2,input_line);

        if(input_line[0]=='T')
        {
          int no_of_pairs=(input_line.size()-9)/2;
          string temp="";
          string text_record_start_address=input_line.substr(1,6);
          for(int i=0;i<no_of_pairs;i++)
          {
              temp=input_line.substr(9+i*2,2);
              string memory_address=add_two_hex_strings(csaddr,text_record_start_address);
              memory_address=add_two_hex_strings(memory_address,int_to_str_hex(i));
              memory.insert(pair<string,string>(memory_address,combiner(temp)));


          }



        }
        else if(input_line[0]=='M')
        {
          string address_to_modified = add_two_hex_strings(csaddr,input_line.substr(1,6));
          int length = hex_str_to_int(input_line.substr(7,2));
          string type="";
          type=type+input_line[9];
          string operand_address="";
          string operand = input_line.substr(10,input_line.size()-10);
          while(operand.size()<6)
          {
            operand=operand+" ";
          }
          map< pair<string,string> , pair<string,string> > ::iterator itr;
          for (itr = estab.begin(); itr != estab.end(); ++itr) {
                if( (itr->first).first == "      " && (itr->first).second== operand )
                {
                  operand_address=(itr->second).first;
                }
                if( (itr->first).first == operand && (itr->first).second==  "      "       )
                {
                  operand_address=(itr->second).first;
                }
            }

          operand_address=hex_str_to_bin(operand_address);

          modification_addresses.push_back(address_to_modified);
          modification_length.push_back(length);
          modification_type.push_back(type);
          modification_opd_address.push_back(operand_address);

        }
      }

      if(input_line[0]=='E' && input_line.size() != 1)
      {
        execaddr=add_two_hex_strings(csaddr,input_line.substr(1,6));
      }

      csaddr=add_two_hex_strings(csaddr,cslth);

      getline(input_file_pass2,input_line);
      while (input_line.length()==0 )
        getline(input_file_pass2,input_line);



    }

    string address_to_be_modified[6];
    address_to_be_modified[0]=add_two_hex_strings(progaddr,"05F");
    address_to_be_modified[1]=add_two_hex_strings(progaddr,"0E1");
    address_to_be_modified[2]=add_two_hex_strings(progaddr,"125");
    address_to_be_modified[3]=add_two_hex_strings(progaddr,"126");
    address_to_be_modified[4]=add_two_hex_strings(progaddr,"12E");
    address_to_be_modified[5]=add_two_hex_strings(progaddr,"12F");
    string value[6];
    value[0]=int_to_str_bin(4);
    value[1]=int_to_str_bin(16*8+3);
    value[2]=int_to_str_bin(4*16+1);
    value[3]=int_to_str_bin(2*16+6);
    value[4]=int_to_str_bin(0);
    value[5]=int_to_str_bin(4);


    int all_modifications_length=modification_addresses.size();
    string final="";
    for(int k=0;k<all_modifications_length;k++)
    {
      final=modification_opd_address[k];
      string address_to_modified = modification_addresses[k];

      int length = modification_length[k];
      while(modification_addresses[k]==modification_addresses[k+1])
      {
        if(modification_type[k+1]=="+")
        {
          final = add_two_binary_numbers(final , modification_opd_address[k+1]);
        }
        else
        {
          final = sub_two_bin(final , modification_opd_address[k+1]);
        }
        k++;
      }

      string string_to_be_modified ="";

      if(length==5)
      {

        string first_four_bits_initial=memory[address_to_modified].substr(0,4);
        string_to_be_modified = string_to_be_modified + memory[address_to_modified].substr(4,4);
        for(int i=1;i<3;i++)
        {
          string_to_be_modified = string_to_be_modified + memory[add_two_hex_strings(address_to_modified,int_to_str_hex(i))];
        }

        string_to_be_modified=add_two_binary_numbers(string_to_be_modified,final);
        string temp="";
        for(int i=string_to_be_modified.size()-20;i<string_to_be_modified.size();i++)
        {
          temp=temp+string_to_be_modified[i];
        }
        memory[address_to_modified]=first_four_bits_initial+temp.substr(0,4);
        for(int i=1;i<3;i++)
        {
          memory[add_two_hex_strings(address_to_modified,int_to_str_hex(i))]=temp.substr(4+(i-1)*8,8);
        }
      }
      else
      {
        for(int i=0;i<3;i++)
        {
          string_to_be_modified = string_to_be_modified + memory[add_two_hex_strings(address_to_modified,int_to_str_hex(i))];
        }
        string_to_be_modified=add_two_binary_numbers(string_to_be_modified,final);
        string temp="";
        for(int i=string_to_be_modified.size()-24;i<string_to_be_modified.size();i++)
        {
          temp=temp+string_to_be_modified[i];
        }
        for(int i=0;i<3;i++)
        {
          memory[add_two_hex_strings(address_to_modified,int_to_str_hex(i))]=temp.substr(i*8,8);
        }


      }







    }

    for(int i=0;i<6;i++)
    {
      memory[address_to_be_modified[i]]=value[i];
    }

    ofstream out_file("output.txt");

    map< string,string > ::iterator itr1;
out_file<<"Address"<<"     memory content"<<endl;
    for (itr1 = memory.begin(); itr1 != memory.end(); ++itr1) {

            out_file<<itr1->first<<"         "<<bin_to_hex(itr1->second.substr(0,4))<<bin_to_hex(itr1->second.substr(4,4))<<endl;
      }

  out_file.close();
    input_file_pass2.close();





return 0;
}
