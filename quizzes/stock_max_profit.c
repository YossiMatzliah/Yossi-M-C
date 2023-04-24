#include <stdio.h>

int StockMaxProfit(int*, int, int*, int*);	

int main()
{
	int arr[] = {50,86,75,55,15,11,1};
	int size = sizeof(arr)/sizeof(arr[0]);
	int sell = 0;
	int buy = 0;
	int profit = 0;	

	profit = StockMaxProfit(arr, size, &buy, &sell);
	if (0 == profit)
	{
		puts("You will have negative value, do not invest!");
	}
	else
	{
		printf("the buy index is %d, the sell index is %d, the profit is %d\n", buy, sell, profit);
	}

	return 0;
}

int StockMaxProfit(int stock_prices[], int size, int *buy, int *sell)
{
    int profit = 0;
    int max_profit = 0;
    int sell_index = 0;
    int buy_index = 0;
    int lowest_price = stock_prices[0];
    *buy = 0;
    *sell = 1;

    while (*sell < size)
    {
        if (stock_prices[*sell] < lowest_price)
        {
            lowest_price = stock_prices[*sell];
            buy_index = *sell;
        }
        else
        {
            profit = stock_prices[*sell] - lowest_price;
            if (profit > max_profit)
            {
                max_profit = profit;
                sell_index = *sell;
                *buy = buy_index;
            }
        }
        *sell = *sell + 1;
    }
    *sell = sell_index;
    return max_profit;
}

