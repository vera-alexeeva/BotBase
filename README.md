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
### Task 3
Через кластеризцию находим аптечки, по сегментам разбитым взависсимости от нахего поля зрения. Находим ближайшую и двигаемся к ней повторяем с начала
### Task 4
Делаем графф карты и через match templay обходим яд и собираем аптечки графом ходим по карте снижая веса в комнатах где мы не были
### Task 5
Через кластеризацию находим снаряды и двигаемся в ту сторону где снарпяды дальше, если у нас перед лицом собственно есть снаряд
### Task 6
Пинки находим через match templay стреляем в них уворачиваемся от фаерболов аналогично 4
### Task 7
через кластеризацию опять же находим врагов и стреляем по ним
### Task 8
крутимся и стреляем когда враг близко, врага через match templay и кластеризацию одновременно
### Task 9
двигаемся вперёд пока match templay по 3 типам врагов не обнаруживает их стреляем по весам (shotgun > minigan > piston) и если врагов нет ставим начальный градус и двигаемся вперёд
### Task 10
Делаем граф куда записываем комнаты которые детектяться через их куски. В каждой комнате проверяем наличие брони и двигаемся к ней если найдём
