int main() {
	int month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int week = 7;
	int begin;
	if (week <= 5)//一月几号开始是周五
		begin = 1 + 5 - week;//一月几号开始是周五
	else
		begin = 8 - (week - 5);
	int mon = 1;
	while(mon <= 12) {
		if (begin == 13) {
			putint(mon);
			begin = begin + 7;
		}
		else{
            if (begin != 13){
			    begin = begin + 7;
            }
        }
		if (begin > month[mon-1]) {
			begin = begin - month[mon-1];
			mon = mon + 1;
		}
	}
	return 0;
}