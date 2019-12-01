CC = g++
SRC = kmeans.cpp
OBJ = $(SRC:.cpp = .o)
CFLAGS = -std=c++98
NumTest: $(OBJ)
	$(CC) $(CFLAGS) -o NumTest $(OBJ)
clean:
	rm -f core *.o NumTest lloyd

lloyd: lloyd.cpp
	g++ -std=c++98 lloyd.cpp -o lloyd

test: NumTest lloyd birch_ds1.txt test_data_uniform_1250000_2.txt
	echo "NumTest k = 3 birch" > output.txt
	./NumTest birch_ds1.txt 3 t >> output.txt
	./NumTest birch_ds1.txt 3 t >> output.txt
	./NumTest birch_ds1.txt 3 t >> output.txt
	echo "" >> output.txt
	echo "NumTest k = 20 birch" >> output.txt
	./NumTest birch_ds1.txt 20 t >> output.txt
	./NumTest birch_ds1.txt 20 t >> output.txt
	./NumTest birch_ds1.txt 20 t >> output.txt
	echo "" >> output.txt
	echo "NumTest k = 100 birch" >> output.txt
	./NumTest birch_ds1.txt 100 t >> output.txt
	./NumTest birch_ds1.txt 100 t >> output.txt
	./NumTest birch_ds1.txt 100 t >> output.txt
	echo "" >> output.txt
	echo "NumTest k = 500 birch" >> output.txt
	./NumTest birch_ds1.txt 500 t >> output.txt
	./NumTest birch_ds1.txt 500 t >> output.txt
	./NumTest birch_ds1.txt 500 t >> output.txt
	echo "" >> output.txt
	echo "" >> output.txt
	echo "lloyd k = 3 birch" >> output.txt
	./lloyd 3 t < birch_ds1.txt >> output.txt
	./lloyd 3 t < birch_ds1.txt >> output.txt
	./lloyd 3 t < birch_ds1.txt >> output.txt
	echo "" >> output.txt
	echo "lloyd k = 20 birch" >> output.txt
	./lloyd 20 t < birch_ds1.txt >> output.txt
	./lloyd 20 t < birch_ds1.txt >> output.txt
	./lloyd 20 t < birch_ds1.txt >> output.txt
	echo "" >> output.txt
	echo "lloyd k = 100 birch" >> output.txt
	./lloyd 100 t < birch_ds1.txt >> output.txt
	./lloyd 100 t < birch_ds1.txt >> output.txt
	./lloyd 100 t < birch_ds1.txt >> output.txt
	echo "" >> output.txt
	echo "lloyd k = 500 birch" >> output.txt
	./lloyd 500 t < birch_ds1.txt >> output.txt
	./lloyd 500 t < birch_ds1.txt >> output.txt
	./lloyd 500 t < birch_ds1.txt >> output.txt
	echo "" >> output.txt
	echo "" >> output.txt
	echo "NumTest k = 3 random_uniform" >> output.txt
	./NumTest test_data_uniform_1250000_2.txt 3 t >> output.txt
	./NumTest test_data_uniform_1250000_2.txt 3 t >> output.txt
	./NumTest test_data_uniform_1250000_2.txt 3 t >> output.txt
	echo "" >> output.txt
	echo "NumTest k = 20 random_uniform" >> output.txt
	./NumTest test_data_uniform_1250000_2.txt 20 t >> output.txt
	./NumTest test_data_uniform_1250000_2.txt 20 t >> output.txt
	./NumTest test_data_uniform_1250000_2.txt 20 t >> output.txt
	echo "" >> output.txt
	echo "NumTest k = 100 random_uniform" >> output.txt
	./NumTest test_data_uniform_1250000_2.txt 100 t >> output.txt
	./NumTest test_data_uniform_1250000_2.txt 100 t >> output.txt
	./NumTest test_data_uniform_1250000_2.txt 100 t >> output.txt
	echo "" >> output.txt
	echo "NumTest k = 500 random_uniform" >> output.txt
	./NumTest test_data_uniform_1250000_2.txt 500 t >> output.txt
	./NumTest test_data_uniform_1250000_2.txt 500 t >> output.txt
	./NumTest test_data_uniform_1250000_2.txt 500 t >> output.txt
	echo "" >> output.txt
	echo "" >> output.txt
	echo "lloyd k = 3 random_uniform" >> output.txt
	./lloyd 3 t < test_data_uniform_1250000_2.txt >> output.txt
	./lloyd 3 t < test_data_uniform_1250000_2.txt >> output.txt
	./lloyd 3 t < test_data_uniform_1250000_2.txt >> output.txt
	echo "" >> output.txt
	echo "lloyd k = 20 random_uniform" >> output.txt
	./lloyd 20 t < test_data_uniform_1250000_2.txt >> output.txt
	./lloyd 20 t < test_data_uniform_1250000_2.txt >> output.txt
	./lloyd 20 t < test_data_uniform_1250000_2.txt >> output.txt
	echo "" >> output.txt
	echo "lloyd k = 100 random_uniform" >> output.txt
	./lloyd 100 t < test_data_uniform_1250000_2.txt >> output.txt
	./lloyd 100 t < test_data_uniform_1250000_2.txt >> output.txt
	./lloyd 100 t < test_data_uniform_1250000_2.txt >> output.txt
	echo "" >> output.txt
	echo "lloyd k = 500 random_uniform" >> output.txt
	./lloyd 500 t < test_data_uniform_1250000_2.txt >> output.txt
	./lloyd 500 t < test_data_uniform_1250000_2.txt >> output.txt
	./lloyd 500 t < test_data_uniform_1250000_2.txt >> output.txt