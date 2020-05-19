#include<iostream>
using namespace std;


#include<sstream>
class var{
	private:
		string _value;
		string _type;
	public:
		var(){_value="0";_type="Int";}
		template<class T>var(T value){
			stringstream sin;
			sin<<value;
			sin>>_value;
			if(_value.length()!=1){
				sin.str("");
				sin.clear();
				sin<<_value;
		    	double d;
				char c;
		    	if(!(sin>>d)){_type="String";return;}
		    	if(sin>>c){_type="String";return;}
				if(d==(long long)(d)){_type="Int";return;}
				int f=_value.find(".");
		    	if(f!=_value.npos){_type="Double";return;}
				else{_type="Bint";return;}
			}
			else if(_value[0]>='1' && _value[0]<='9'){_type="Int";return;}
			else{_type="Char";return;}
		}
		friend ostream & operator<<(ostream &out,const var &a){out<<a._value;return out;}
    	friend istream & operator>>(istream &in,var &a){string t;in>>t;a=t;return in;}
		explicit operator bool(){if(_value=="" || _value=="0")return 0;else return 1;}
		explicit operator int(){return toInt();}
		int    length(){return _value.length();}
		string type(){return _type;}
		string substr(var pos,var len=0){
			return _value.substr(pos.toInt(),len.toInt());
		}
		double toDouble(string me="")const{
			stringstream sin(_value);
			double t;
			char c;
			if(!(sin>>t)){
				cerr<<"ERROR in "<<me<<"/toDouble()"<<endl;
				exit(1);
			}
			if(sin>>c){
				cerr<<"ERROR in "<<me<<"/toDouble()"<<endl;
				exit(1);
			}
			return t;
		}
		int    toInt(){return (long long)toDouble();}
		string toString(){return _value;}
		var    operator +  (var other){
			if(_type=="Bint"||other._type=="Bint"){
				cerr<<"ERROR: Bint can't do this operation:+"<<endl;
				exit(1);
			}
			else if(_type=="String"||other._type=="String"){
				return _value+other._value;
			}
			return toDouble(_value+"in plus")+other.toDouble(other._value+"in plus");
		}
		var    operator -  (var other){
			if(_type=="String"||other._type=="String"){
				cerr<<"ERROR: String can't do this operation:-"<<endl;
				exit(1);
			}
			else if(_type=="Bint"||other._type=="Bint"){
				cerr<<"ERROR: Bint can't do this operation:-"<<endl;
				exit(1);
			}
			return toDouble(_value+"in minus")-other.toDouble(other._value+"in minus");
		}
		var    operator *  (var other){
			if(_type=="Bint"||other._type=="Bint"){
				cerr<<"ERROR: Bint can't do this operation:*"<<endl;
				exit(1);
			}
			else if(_type=="String"&&other._type=="String"){
				cerr<<"ERROR: String can't do this operation:*"<<endl;
				exit(1);
			}
			else if(_type=="String"&&other._type=="Int"){
				var temp="";
				for(var i=0;i<other;i++)temp+=_value;
				return temp;
			}
			return toDouble(_value+"in times")*other.toDouble(other._value+"in times");
		}
		var    operator /  (var other){
			if(_type=="String"||other._type=="String"){
				cerr<<"ERROR: String can't do this operation:/"<<endl;
				exit(1);
			}
			else if(_type=="Bint"||other._type=="Bint"){
				cerr<<"ERROR: Bint can't do this operation:/"<<endl;
				exit(1);
			}
			return toDouble(_value+"in divided")/other.toDouble(other._value+"in didvided");
		}
		var    operator %  (var other){
			if(_type=="String"||other._type=="String"){
				cerr<<"ERROR: String can't do this operation:%"<<endl;
				exit(1);
			}
			else if(_type=="Double"||other._type=="Double"){
				cerr<<"ERROR: Double can't do this operation:%"<<endl;
				exit(1);
			}
			else if(_type=="Bint"||other._type=="Bint"){
				cerr<<"ERROR: Bint can't do this operation:%"<<endl;
				exit(1);
			}
			return toInt()%other.toInt();
		}
		var    operator ++ (){*this=*this+1;return *this;}
		var    operator ++ (int){*this=*this+1;return *this-1;}
		var    operator -- (){*this=*this-1;return *this;}
		var    operator -- (int){*this=*this-1;return *this+1;}
		void   operator += (var other){*this=*this+other;}
		void   operator -= (var other){*this=*this-other;}
		void   operator *= (var other){*this=*this*other;}
		void   operator /= (var other){*this=*this/other;}
		void   operator %= (var other){*this=*this%other;}
		bool   operator != (var other)const{return _value!=other._value;}
		bool   operator == (var other)const{return _value==other._value;}
		bool   operator <  (var other)const{
			if((_type=="String" && other._type=="String")||(_type=="Char" && other._type=="Char")){
				return _value<other._value;
			}
			else return toDouble()<other.toDouble();
		}
		bool   operator >  (var other)const{return other<*this;}
		bool   operator <= (var other)const{return !(other<*this);}
		bool   operator >= (var other)const{return !(*this<other);}
		char&  operator [] (var i){return _value.at(i.toInt());}
};
