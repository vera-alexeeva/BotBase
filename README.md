# DOOM openCV summer practice

### Task 1
![Task 1](https://j.gifs.com/1WOWLq.gif "task 1")


**Центр ищется по фиксированному у**


```C++
int start, end, center;
start = -100;

for (int x = 0; x < 640; x++) {
	if (greyscale.at<unsigned char>(225, x) > 130) {
		if (start < 0) start = x;
    end = x;
  }
}

center = start + (end - start) / 2;
```



### Task 2
![Task 2](https://j.gifs.com/oVoV5Y.gif "task 2")


**Угол подобран методом тыка, и полученный коофицент используется для расчёта последующих углов**


```C++
//center same as in task 1
float angle;
angle = asin((289.0 - center) / 190.14401)*(180/3.14159265358979323846);
// arcsin((289.0 - center) / 190.14401))*(180/pi)
```
