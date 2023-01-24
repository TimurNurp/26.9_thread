#include <thread>
#include <random>
#include <chrono>
#include <iostream>
 
size_t* creat_arr(const size_t& n){
    size_t *arr = new size_t[n];

    for (int i=0;i < n; ++i)
        arr[i] = (static_cast<size_t>(rand() % 10)) + 1;

    return arr;    
}

 void arr_sum(size_t* arr, size_t& n, size_t& sum){
   
    for (int i = 0; i < n;  ++i)
        sum +=arr[i];

    return; 

 }

int* splittingUp(int* arr, const int& n, const int& div, int& k) {


    int* arr_div = new int[k];

    for (int i = 0; i < k; ++i)
        arr_div[i] = i * k;

    return arr_div;
}

int main()
{
   
    size_t n, m;
    std::cout << "enter number of array size" << std::endl;
    std::cin >> n;
    std::cout << "enter number of thread" << std::endl;
    std::cin >> m;

    size_t* arr = creat_arr(n);//созданем массив случайных чисел

    //for (size_t i = 0; i < n; ++i)
    //    std::cout << arr[i] << " ";
    //std::cout << std::endl;

    size_t sumNumberInArray = 0;

    auto start = std::chrono::steady_clock::now();

    arr_sum(arr, n, sumNumberInArray);

    auto end = std::chrono::steady_clock::now();

    std::cout << "the sum of the numbers in the array (no thread):" << sumNumberInArray << std::endl;

    std::cout << "Elapsed time in microseconds: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " ms" << std::endl;



    size_t sizeSubArr = 1;  //размерность массивов на которые будет разделен основной массив чисел

    if (n != 0)
        sizeSubArr = n / m;
    else
        return 1;

    size_t* sumValuesArr = new size_t[m];//сюда буду сохранять сумму с потоков
    for (size_t i = 0; i < m; ++i)
        sumValuesArr[i] = 0;

    std::thread* myThreads = new std::thread[m]; //создаю массив потоков размерностью М, занной пользователем

    start = std::chrono::steady_clock::now();

    for (size_t i = 0; i < m; ++i)
        myThreads[i] = std::thread(arr_sum, arr+(i*sizeSubArr), std::ref(sizeSubArr), std::ref(sumValuesArr[i])); //инициализируем потоки //  std::ref(sumValuesArr[i]) (arr + (i * sizeSubArr))
   
    for (size_t i = 0; i < m; ++i)
        myThreads[i].join();

    end = std::chrono::steady_clock::now();

    //for (size_t i = 0; i < m; ++i)
    //    std::cout << sumValuesArr[i]<<" ";
    //std::cout << std::endl;

    sumNumberInArray = 0;
    arr_sum(sumValuesArr, m, sumNumberInArray);


    std::cout << "the sum of the numbers in the array (with thread): " << sumNumberInArray << std::endl;
    std::cout << "Elapsed time in microseconds: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " ms" << std::endl;

    delete[] arr, sumValuesArr;
    return 0;
}