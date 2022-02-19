# Florian (112), Elias (111) - 2021/2022 Profilkurs Informatik

# region initialization code
# imports
import pygame
import random
import time
from typing import List
# from replit import audio

# CHANGE ME choose between imperativ and object oriented
# only insertSort() has the imperativ code implemented
imperativ: bool = False

# window size
height: int = 300
width: int = 300

MIN_FREQUENCY: int = 100
MAX_FREQUENCY: int = 500

# start enigne
pygame.init()
# initialize screen (with it's size)
screen = pygame.display.set_mode((height, width))
# screen background color
screen.fill((0, 0, 0))
# endregion

# region imperativ code


def drawArray(array: List[int], coloredIndexes: List[int] or int = -1, delay: float = 0.01) -> None:
    def drawBar(array: List[int], index: int, coloredIndexes: List[int]) -> None:
        # calculate bar width
        barWidth: float = width / len(array)

        # ratio between the screen height and the biggest value in the array
        ratio: float = height / Sorting.utils.maxValue(array)
        barHeight: float = array[index] * ratio

        color = (255, 0, 0)  # default color
        if (index % 2 == 0):
            color = (0, 0, 255)
        if (index in coloredIndexes):
            color = (0, 255, 0)  # current bar

        # draw the line to the screen with the correct position
        coords = ((barWidth * index, height - barHeight), (barWidth,
                                                           barHeight))
        pygame.draw.rect(screen, color, coords)

    if (len(array) > width):
        return  # too big to draw

    # checks if the coloredIndex is an array or a number
    if (not isinstance(coloredIndexes, list)):
        # and sets it to a list if it was a number
        coloredIndexes = [coloredIndexes]

    # refresh background
    screen.fill((0, 0, 0))

    # draw each bar to the screen
    for i in range(len(array)):
        drawBar(array, i, coloredIndexes)

    # update display once
    pygame.display.update()

    # hold for [delay] time
    time.sleep(delay)


def startTimer() -> int:
    return int(round(time.time() * 1000))


def endTimer(startingTime: int) -> int:
    return int(round(time.time() * 1000)) - startingTime
# endregion

# region object oriented code


class Sorting:
    class visualization:
        # MAGIC. DO NOT TOUCH!
        def drawArray(array: List[int], coloredIndexes: List[int] or int = -1, delay: float = 0.01) -> None:
            if (len(array) > width):
                return  # too big to draw

            # checks if the coloredIndex is an array or a number
            if (not isinstance(coloredIndexes, list)):
                # and sets it to a list if it was a number
                coloredIndexes = [coloredIndexes]

            # refresh background
            screen.fill((0, 0, 0))

            # draw each bar to the screen
            for i in range(len(array)):
                Sorting.visualization.drawBar(array, i, coloredIndexes)

            # region Audio
            minFreqRatio = Sorting.utils.minValue(array)/MIN_FREQUENCY
            maxFreqRatio = Sorting.utils.maxValue(array)/MAX_FREQUENCY

            # FIXME
            freq: float = minFreqRatio + \
                (array[coloredIndexes[0]] * (maxFreqRatio - minFreqRatio))

            # TODO audio frequency (and delay)
            Sorting.audio.play(delay, freq)
            # endregion

            # update display once
            pygame.display.update()

            # hold for [delay] time
            time.sleep(delay)

        def drawBar(array: List[int], index: int, coloredIndexes: List[int]) -> None:
            # calculate bar width
            barWidth: float = width / len(array)

            # ratio between the screen height and the biggest value in the array
            ratio: float = height / Sorting.utils.maxValue(array)
            barHeight: float = array[index] * ratio

            # region set color
            maxVal: int = Sorting.utils.maxValue(array)
            minVal: int = Sorting.utils.minValue(array)
            diffVal: int = maxVal - minVal
            if (diffVal <= 0):
                diffVal = 1  # error case
            # 0% = minVal, 100% = maxVal, 50% = (maxVal-minVal)/2
            valuePercent: float = (array[index] - minVal) / diffVal
            indexPercent: float = 1 - \
                ((len(array) - 1) - index)/(len(array) - 1)

            redChannel = valuePercent * 255
            if (indexPercent > .5):
                redChannel = redChannel * indexPercent
            greenChannel = 0
            blueChannel = (1 - valuePercent) * 255
            if (indexPercent < .5):
                redChannel = redChannel * (1-indexPercent)
            # default color
            color = (redChannel, greenChannel, blueChannel)

            if (index in coloredIndexes):
                color = (255, 255, 255)  # current bar
            # endregion

            # draw the line to the screen with the correct position
            coords = ((barWidth * index, height - barHeight), (barWidth,
                                                               barHeight))
            pygame.draw.rect(screen, color, coords)

    class timer:
        # constructor, starts the timer
        def __init__(self):
            self.startTimer()

        # destructor, ends the timer
        def __del__(self):
            self.stopTimer()

        # starts the time recording
        def startTimer(self) -> None:
            # set the start time to the current time
            self.startTime: int = int(round(time.time() * 1000))

            # print to the console the current state of the timer
            print("[TIMER]: Started timer")

        # ends the time recording
        def stopTimer(self) -> float:
            # calculate difference from starting time and current time
            difference: float = self.calculateTime()

            # reset the start time
            self.startTime: int = 0

            # print the values to the console
            print(Sorting.utils.timeToString(difference))
            print("[TIMER]: Ended timer")

            return difference

        # calculate the time between the start time and the current time in ms
        def calculateTime(self) -> float:
            return int(round(time.time() * 1000)) - self.startTime

    class audio:
        # play a certain frequency
        def play(seconds: float, frequency: float):
            # audio.play_tone(seconds, frequency, 0)
            x = 0

    class utils:
        # generate an array with elementCount amount of values
        # between minValue and maxValue (inclusiv)
        def generateRandomArray(elementCount: int, minValue: int, maxValue: int) -> List[int]:
            return [random.randint(minValue, maxValue) for _ in range(elementCount)]

        def maxValue(list: List[int]) -> int:
            maxVal: int = list[0]
            for v in list:
                if maxVal < v:
                    maxVal = v
            return maxVal

        def minValue(list: List[int]) -> int:
            minVal: int = list[0]
            for v in list:
                if minVal > v:
                    minVal = v
            return minVal

        def timeToString(ms: float) -> str:
            # helper function to get the correct string ("", "singular", "plural with s")
            def getStr(val: int, strV: str):
                if val != 0:
                    return str(val) + " " + strV + ("s " if val > 1 else " ")
                else:
                    return ""

            # calculate the times
            min = (ms // 1000) // 60
            sec = ms // 1000 % 60
            ms = ms % 1000

            ansStr: str = ""

            ansStr = ansStr + getStr(min, "minute")
            ansStr = ansStr + getStr(sec, "second")
            ansStr = ansStr + getStr(ms, "millisecond")

            return ansStr

    class sortingAlgs:
        def bubbleSort(list: List[int], drawToDisplay: bool = False):
            t = Sorting.timer()  # start timer

            for i in range(len(list) - 1):
                for j in range(len(list) - i - 1):

                    # draw array to the screen
                    if (drawToDisplay):
                        Sorting.visualization.drawArray(list, j)

                    if list[j] > list[j + 1]:
                        list[j], list[j + 1] = list[j + 1], list[j]

            return list

        def shakerSort(list: List[int], drawToDisplay: bool = False):
            t = Sorting.timer()  # start timer

            for x in range(len(list)):
                for i in range(1, len(list)*2-2):
                    if(i > len(list)-1):
                        i = len(list)*2-i-2
                    if(list[i-1] > list[i]):
                        list[i], list[i-1] = list[i-1], list[i]

                    # draw array to screen
                    if (drawToDisplay):
                        Sorting.visualization.drawArray(list, i)

            return list

        def insertSort(list: List[int], drawToDisplay: bool = False):
            # gets destroyed by garbage collection and thus ends the timer
            # with it's destructor
            timerObj = 0

            startingTime = 0
            if imperativ:
                startingTime = startTimer()
                print("Started timer")
            else:
                timerObj = Sorting.timer()  # start timer

            for i in range(1, len(list)):
                for y in range(i, 0, -1):
                    if list[y] < list[y - 1]:

                        oldYValue = list[y]
                        list[y] = list[y - 1]
                        list[y - 1] = oldYValue
                    else:
                        break

                    # draw array to screen
                    if (drawToDisplay):
                        if imperativ:
                            drawArray(list, y, 0.005)
                        else:
                            Sorting.visualization.drawArray(
                                list, y, 0.005)

            if imperativ:
                print("Ended timer with: " +
                      str(endTimer(startingTime)) + "ms duration")

            return list
# endregion


# main entry
randArray = Sorting.utils.generateRandomArray(
    elementCount=100, minValue=0, maxValue=100)
sortedArray = Sorting.sortingAlgs.insertSort(randArray, True)
print(sortedArray)

# region hold window open until keypress
holdOpen = True
while holdOpen:
    events = pygame.event.get()
    for event in events:
        if event.type == pygame.KEYDOWN:
            holdOpen = False
# endregion
