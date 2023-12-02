int change(char* s);
bool backspaceCompare(char* s, char* t) {
    int ls1 = change(s);
    int ls2 = change(t);
    if(ls1 != ls2) return false;
    else{
        if(strncmp(s,t,ls1)==0) return true;
        else return false;
    }
}

int change(char* s){
    int fast = 0,slow = 0;
    int len = strlen(s);
    for(; fast<len; fast++){
        if(s[fast]=='#'){
            if(slow !=0 ) slow--;
        }
        else{
            s[slow++] = s[fast];
        }
    }
    return slow;
}