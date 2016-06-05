void InsertSort(int* arry, int start, int p) {
	for (int i = start + 1; i <= p; i++)
	{
		int te = arry[i];
		int j = i;
		while (arry[j] < arry[j - 1] && j > start)
		{
			arry[j] = arry[j - 1];
			arry[j - 1] = te;
			j--;
		}
	}
}