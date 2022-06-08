double my_div(double first, double second)
{
	if((second-0.0) < 0.00000000000000001){
		return first;
	}
	return first/second;
}