		#include <iostream>
		#include <stdio.h>
		#include <time.h>
		#include <math.h>
		
		int main(void)
		{
			time_t now, now2;
			struct tm present_time;
			
			double diff_time_seconds;
			
			int menu_item = 0;
			
			char stock_item_string[5][10];
			
			float vwsp_num[5] = {0, 0, 0, 0, 0};
			float vwsp_denom[5] = {0, 0, 0, 0, 0};
			float vwsp_result[5] = {0, 0, 0, 0, 0};
			
			float geo_mean_product[5] = {0, 0, 0, 0, 0};
			float geo_mean_result[5] = {0, 0, 0, 0, 0};
			int geo_mean_stock_item_population = 0;
			
			time_t trade_record_time_para_pass;
			time_t trade_record_time[1000];
			int trade_record_stock_item[1000];
			int trade_record_quantity_of_shares[1000];
			int trade_record_buy_or_sell[1000];
			float trade_record_traded_price[1000];
			int trade_record_population = 0;
			int trade_record_index = 0;
			
			int quantity_of_shares;
			int buy_or_sell;
			float traded_price;
			
			int stock_item;
			float price;
			float dividend_yield;
			float p_e_ratio;
			
			int type[5] = {0, 0, 0, 1, 0};
			float last_dividend[5] = {0, 8, 23, 8, 13};
			float fixed_dividend[5] = {0, 0, 0, 2, 0};
			float par_value[5] = {100, 100, 60, 100, 250};
			
			int share_population[5] = {0, 0, 0, 0, 0};
			
			strcpy(stock_item_string[0], "TEA");
			strcpy(stock_item_string[1], "POP");
			strcpy(stock_item_string[2], "ALE");
			strcpy(stock_item_string[3], "GIN");
			strcpy(stock_item_string[4], "JOE");
			
			trade_record_population = 0;
			
			time(&now);
			
			do
			{
				printf("Menu\n");
				printf("====\n\n");
				printf("[0] Price input query (for a given stock_item) => {dividend_yield, p_e_ratio}\n");
				printf("[1] Record a trade\n");
				printf("[2] Calculate Volume Weighted Stock Price\n");
				printf("[3] Calculate GBCE All Share Index using the geometric mean of prices for all stocks\n");
				printf("[4] Exit\n");
				printf("menu_item: ");
				scanf("%d", &menu_item);
				
				if (menu_item == 0)
				{
					printf("Price input query\n");
					printf("=================\n\n");
					
					printf("Stock:-\n");
					printf("[0] TEA-\n");
					printf("[1] POP-\n");
					printf("[2] ALE-\n");
					printf("[3] GIN-\n");
					printf("[4] JOE-\n\n");
					printf("Choice: ");
					scanf("%d", &stock_item);
					
					printf("Price: ");
					scanf("%f", &price);
					
					if (price <= 0)
					{
						printf("CALCULATION ABORTED: PRICE CANNOT BE ZERO OR LESS\n");
					}
					else
					{
						if (type[stock_item] == 0)
						{
							dividend_yield = last_dividend[stock_item] / price;
							printf("dividend_yield = %f\n", dividend_yield);
							
							if (last_dividend[stock_item] == 0)
							{
								printf("p_e_ratio = INFINITY\n");
							}
							else
							{
								p_e_ratio = price/last_dividend[stock_item];
								printf("p_e_ratio = %f\n", p_e_ratio);
							}
						}
						else
						{
							dividend_yield = (fixed_dividend[stock_item]*par_value[stock_item]) / price;
							printf("dividend_yield = %f\n", dividend_yield);
							if (fixed_dividend[stock_item] == 0)
							{
								printf("p_e_ratio = INFINITY\n");
							}
							else
							{
								p_e_ratio = price/fixed_dividend[stock_item];
								printf("p_e_ratio = %f\n", p_e_ratio);
							}
						}
						
						
						
					}
				}
				else if (menu_item == 1)
				{
					printf("TRADE\n");
					printf("=====\n\n");
					
					printf("Stock:-\n");
					for (stock_item = 0; stock_item < 5; stock_item++)
						printf("[%d] %s\n", stock_item, stock_item_string[stock_item]);
					
					printf("\n");
					printf("Choice: ");
					scanf("%d", &stock_item);
					
					printf("Quantity of shares: ");
					scanf("%d", &quantity_of_shares);
					
					printf("[0] Buy or [1] Sell: ");
					scanf("%d", &buy_or_sell);
					
					if (buy_or_sell == 0)
					{
						printf("Traded Price: ");
						scanf("%f", &traded_price);
						time(&trade_record_time_para_pass);
						trade_record_time[trade_record_population] = trade_record_time_para_pass;
						trade_record_stock_item[trade_record_population] = stock_item;
						trade_record_quantity_of_shares[trade_record_population] = quantity_of_shares;
						trade_record_buy_or_sell[trade_record_population] = 0;
						trade_record_traded_price[trade_record_population] = traded_price;
						trade_record_population++;
						
						share_population[stock_item] += quantity_of_shares;
						
						printf("TRADE COMPLETED SUCCESSFULLY!\n");
					}
					else if ((buy_or_sell == 1) && (share_population[stock_item] == 0))
					{
						printf("NO SHARES TO SELL => TRADE ABORTED\n");
					}
					else if ((buy_or_sell == 1) && (quantity_of_shares > share_population[stock_item]))
					{
						printf("INSUFFICIENT NUMBER OF SHARES TO SELL => TRADE ABORTED\n");
					}
					else // ((buy_or_sell == 1) && (quantity_of_shares <= share_population[stock_item]))
					{
						printf("Traded Price: ");
						scanf("%f", &traded_price);
						time(&trade_record_time_para_pass);
						trade_record_time[trade_record_population] = trade_record_time_para_pass;
						trade_record_stock_item[trade_record_population] = stock_item;
						trade_record_quantity_of_shares[trade_record_population] = quantity_of_shares;
						trade_record_buy_or_sell[trade_record_population] = 1;
						trade_record_traded_price[trade_record_population] = traded_price;
						trade_record_population++;
						
						share_population[stock_item] -= quantity_of_shares;
						
						printf("TRADE COMPLETED SUCCESSFULLY!\n");
					}
				}
				else if (menu_item == 2)
				{
					time(&now2);
					
					printf("Calculate Volume Weighted Stock Price - Time Windowed\n");
					printf("=====================================================\n\n");
					
					present_time = *localtime(&now2);
					printf ("Current local time and date: %s", asctime(&present_time));
					
					if (trade_record_population == 0)
					{
						printf("ABORTED AS NO TRADES HAVE BEEN RECORDED\n");
					}
					else
					{
						for (stock_item = 0; stock_item < 5; stock_item++)
						{
							vwsp_num[stock_item] = 0;
							vwsp_denom[stock_item] = 0;
						}
					
						for (trade_record_index = 0; trade_record_index < trade_record_population; trade_record_index++)
						{
							diff_time_seconds = difftime(now2, trade_record_time[trade_record_index]);
							if (diff_time_seconds < (15.000000*60.000000))
							{
								vwsp_num[trade_record_stock_item[trade_record_index]] += trade_record_traded_price[trade_record_index] * (float)trade_record_quantity_of_shares[trade_record_index];
								vwsp_denom[trade_record_stock_item[trade_record_index]] += (float)trade_record_quantity_of_shares[trade_record_index];
							}
						}
						
						for (stock_item = 0; stock_item < 5; stock_item++)
						{
							if (vwsp_denom[stock_item] == 0)
							{
								vwsp_result[stock_item] = 0.000000;
								printf("%d\t%s\t%f\n", stock_item, stock_item_string[stock_item], vwsp_result[stock_item]);
							}
							else
							{
								vwsp_result[stock_item] = vwsp_num[stock_item] / vwsp_denom[stock_item];
								printf("%d\t%s\t%f\n", stock_item, stock_item_string[stock_item], vwsp_result[stock_item]);
							}
						}
					}
				}
				else if (menu_item == 3)
				{
					printf("Calculate GBCE All Share Index using the geometric mean of prices for all stocks\n");
					printf("================================================================================\n\n");
					
					
					if (trade_record_population == 0)
					{
						printf("ABORTED AS NO TRADES HAVE BEEN RECORDED\n");
					}
					else
					{
						for (stock_item = 0; stock_item < 5; stock_item++)
						{
							geo_mean_product[stock_item] = 0;
						}
						
						
						for (stock_item = 0; stock_item < 5; stock_item++)
						{
							geo_mean_result[stock_item] = 0.000000;
							
							geo_mean_stock_item_population = 0;
							for (trade_record_index = 0; trade_record_index < trade_record_population; trade_record_index++)
							{
								if (trade_record_stock_item[trade_record_index] == stock_item)
								{
									if ((geo_mean_product[stock_item] == 0.000000) && (trade_record_traded_price[trade_record_index] != 0.000000))
										geo_mean_product[trade_record_stock_item[trade_record_index]] = trade_record_traded_price[trade_record_index];
									else
										geo_mean_product[trade_record_stock_item[trade_record_index]] *= trade_record_traded_price[trade_record_index];
									geo_mean_stock_item_population++;
								}
							}
							
							if (geo_mean_stock_item_population == 0)
								geo_mean_result[stock_item] = geo_mean_product[stock_item];
							else
								geo_mean_result[stock_item] = pow(geo_mean_product[stock_item], 1.000000/(float)geo_mean_stock_item_population);
						}
						
						for (stock_item = 0; stock_item < 5; stock_item++)
						{
							printf("%d\t%s\t%f\n", stock_item, stock_item_string[stock_item], geo_mean_result[stock_item]);
						}
					}
				}
			}
			while (menu_item != 4);
			
			return 0;
		}