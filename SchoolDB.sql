-- phpMyAdmin SQL Dump
-- version 4.6.6deb4+deb9u2
-- https://www.phpmyadmin.net/
--
-- Хост: localhost:3306
-- Время создания: Май 15 2022 г., 15:08
-- Версия сервера: 10.1.48-MariaDB-0+deb9u2
-- Версия PHP: 7.0.33-0+deb9u12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `SchoolDB`
--

-- --------------------------------------------------------

--
-- Структура таблицы `ClassNames`
--

CREATE TABLE `ClassNames` (
  `ClassNameID` int(11) NOT NULL,
  `ClassNameNumber` varchar(5) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Дамп данных таблицы `ClassNames`
--

INSERT INTO `ClassNames` (`ClassNameID`, `ClassNameNumber`) VALUES
(1, 'А8'),
(2, 'А9'),
(3, 'А10'),
(4, 'Б7'),
(5, 'Б11'),
(14, 'К5');

-- --------------------------------------------------------

--
-- Структура таблицы `ClassRooms`
--

CREATE TABLE `ClassRooms` (
  `ClassRoomID` int(11) NOT NULL,
  `ClassRoomName` varchar(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Дамп данных таблицы `ClassRooms`
--

INSERT INTO `ClassRooms` (`ClassRoomID`, `ClassRoomName`) VALUES
(1, '110'),
(2, '111'),
(3, '112'),
(4, '210'),
(5, '211'),
(6, '212'),
(13, '789');

-- --------------------------------------------------------

--
-- Структура таблицы `School`
--

CREATE TABLE `School` (
  `SchoolID` int(11) NOT NULL,
  `SchoolName` varchar(45) DEFAULT NULL,
  `Adress` varchar(45) DEFAULT NULL,
  `FoundingDate` date DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Дамп данных таблицы `School`
--

INSERT INTO `School` (`SchoolID`, `SchoolName`, `Adress`, `FoundingDate`) VALUES
(1, 'Гимназия № 34', 'Рябикова, д.25А (1 корпус)', '1985-05-16'),
(2, 'МОУ СОШ №72', 'пр. Вр. Сурова, 11', '1991-07-13'),
(3, 'МОУ СОШ №86', 'Карбышева, дом 38', '1980-01-11'),
(4, 'МОУ СОШ №51', 'Артема, 8', '1977-10-25'),
(5, 'МОУ СОШ №78', 'Фруктовая, 5', '1955-11-21'),
(6, 'МОУ СОШ №78', 'Фруктовая, 3', '1911-05-22'),
(7, 'МОУ СОШ №78', 'Фруктовая, 7', '1977-02-23');

-- --------------------------------------------------------

--
-- Структура таблицы `Student`
--

CREATE TABLE `Student` (
  `StudentID` int(11) NOT NULL,
  `StudentName` varchar(80) DEFAULT NULL,
  `Gender` varchar(10) DEFAULT NULL,
  `Birthday` date DEFAULT NULL,
  `PhoneNumber` varchar(15) DEFAULT NULL,
  `SchoolID` int(11) DEFAULT NULL,
  `AverageScore` double DEFAULT NULL,
  `ClassNameID` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Дамп данных таблицы `Student`
--

INSERT INTO `Student` (`StudentID`, `StudentName`, `Gender`, `Birthday`, `PhoneNumber`, `SchoolID`, `AverageScore`, `ClassNameID`) VALUES
(1, 'Иванов Иван Иванович', 'Мужской', '2002-11-25', '88005553535', 1, 4.5, NULL),
(2, 'Иванов Иван Иванович', 'Мужской', '2002-11-25', '88005553535', 1, 4.5, NULL);

-- --------------------------------------------------------

--
-- Структура таблицы `Subjects`
--

CREATE TABLE `Subjects` (
  `SubjectID` int(11) NOT NULL,
  `SubjectName` varchar(25) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Дамп данных таблицы `Subjects`
--

INSERT INTO `Subjects` (`SubjectID`, `SubjectName`) VALUES
(1, 'Русский язык'),
(2, 'Математика'),
(3, 'Физика'),
(4, 'Литература');

-- --------------------------------------------------------

--
-- Структура таблицы `Teacher`
--

CREATE TABLE `Teacher` (
  `TeacherID` int(11) NOT NULL,
  `TeacherName` varchar(80) DEFAULT NULL,
  `Gender` varchar(10) DEFAULT NULL,
  `Birthday` date DEFAULT NULL,
  `PhoneNumber` varchar(15) DEFAULT NULL,
  `WorkExperience` double DEFAULT NULL,
  `Education` varchar(40) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Дамп данных таблицы `Teacher`
--

INSERT INTO `Teacher` (`TeacherID`, `TeacherName`, `Gender`, `Birthday`, `PhoneNumber`, `WorkExperience`, `Education`) VALUES
(1, 'Иванов Иван Иванович', 'Мужской', '2002-11-25', '88005553535', 4.5, 'Высшее'),
(2, 'Иванова Ивана Ивановна', 'Женский', '2002-11-25', '88005553535', 4.5, 'Высшее');

-- --------------------------------------------------------

--
-- Структура таблицы `TeacherAndSchool`
--

CREATE TABLE `TeacherAndSchool` (
  `TeacherAndSchoolID` int(11) NOT NULL,
  `TeacherID` int(11) DEFAULT NULL,
  `SchoolID` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Дамп данных таблицы `TeacherAndSchool`
--

INSERT INTO `TeacherAndSchool` (`TeacherAndSchoolID`, `TeacherID`, `SchoolID`) VALUES
(1, 1, 1),
(2, 2, 5);

-- --------------------------------------------------------

--
-- Структура таблицы `TeacherAndSubjects`
--

CREATE TABLE `TeacherAndSubjects` (
  `TeacherAndSubjectsID` int(11) NOT NULL,
  `TeacherID` int(11) DEFAULT NULL,
  `SubjectID` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Дамп данных таблицы `TeacherAndSubjects`
--

INSERT INTO `TeacherAndSubjects` (`TeacherAndSubjectsID`, `TeacherID`, `SubjectID`) VALUES
(1, 1, 3),
(2, 2, 1);

-- --------------------------------------------------------

--
-- Структура таблицы `Timetable`
--

CREATE TABLE `Timetable` (
  `TimeTableID` int(11) NOT NULL,
  `SchoolID` int(11) DEFAULT NULL,
  `Weekday` varchar(15) DEFAULT NULL,
  `ClassNameID` int(11) DEFAULT NULL,
  `SubjectID` int(11) DEFAULT NULL,
  `TeacherID` int(11) DEFAULT NULL,
  `ClassRoomID` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Дамп данных таблицы `Timetable`
--

INSERT INTO `Timetable` (`TimeTableID`, `SchoolID`, `Weekday`, `ClassNameID`, `SubjectID`, `TeacherID`, `ClassRoomID`) VALUES
(4, 2, 'Понедельник', 4, 2, 2, 1);

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `ClassNames`
--
ALTER TABLE `ClassNames`
  ADD PRIMARY KEY (`ClassNameID`);

--
-- Индексы таблицы `ClassRooms`
--
ALTER TABLE `ClassRooms`
  ADD PRIMARY KEY (`ClassRoomID`);

--
-- Индексы таблицы `School`
--
ALTER TABLE `School`
  ADD PRIMARY KEY (`SchoolID`);

--
-- Индексы таблицы `Student`
--
ALTER TABLE `Student`
  ADD PRIMARY KEY (`StudentID`),
  ADD KEY `SchoolID` (`SchoolID`),
  ADD KEY `ClassNameID` (`ClassNameID`);

--
-- Индексы таблицы `Subjects`
--
ALTER TABLE `Subjects`
  ADD PRIMARY KEY (`SubjectID`);

--
-- Индексы таблицы `Teacher`
--
ALTER TABLE `Teacher`
  ADD PRIMARY KEY (`TeacherID`);

--
-- Индексы таблицы `TeacherAndSchool`
--
ALTER TABLE `TeacherAndSchool`
  ADD PRIMARY KEY (`TeacherAndSchoolID`),
  ADD KEY `TeacherID` (`TeacherID`),
  ADD KEY `SchoolID` (`SchoolID`);

--
-- Индексы таблицы `TeacherAndSubjects`
--
ALTER TABLE `TeacherAndSubjects`
  ADD PRIMARY KEY (`TeacherAndSubjectsID`),
  ADD KEY `TeacherID` (`TeacherID`),
  ADD KEY `SubjectID` (`SubjectID`);

--
-- Индексы таблицы `Timetable`
--
ALTER TABLE `Timetable`
  ADD PRIMARY KEY (`TimeTableID`),
  ADD KEY `SchoolID` (`SchoolID`),
  ADD KEY `ClassNameID` (`ClassNameID`),
  ADD KEY `SubjectID` (`SubjectID`),
  ADD KEY `TeacherID` (`TeacherID`),
  ADD KEY `ClassRoomID` (`ClassRoomID`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `ClassNames`
--
ALTER TABLE `ClassNames`
  MODIFY `ClassNameID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=16;
--
-- AUTO_INCREMENT для таблицы `ClassRooms`
--
ALTER TABLE `ClassRooms`
  MODIFY `ClassRoomID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;
--
-- AUTO_INCREMENT для таблицы `School`
--
ALTER TABLE `School`
  MODIFY `SchoolID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=17;
--
-- AUTO_INCREMENT для таблицы `Student`
--
ALTER TABLE `Student`
  MODIFY `StudentID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;
--
-- AUTO_INCREMENT для таблицы `Subjects`
--
ALTER TABLE `Subjects`
  MODIFY `SubjectID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;
--
-- AUTO_INCREMENT для таблицы `Teacher`
--
ALTER TABLE `Teacher`
  MODIFY `TeacherID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT для таблицы `TeacherAndSchool`
--
ALTER TABLE `TeacherAndSchool`
  MODIFY `TeacherAndSchoolID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT для таблицы `TeacherAndSubjects`
--
ALTER TABLE `TeacherAndSubjects`
  MODIFY `TeacherAndSubjectsID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
--
-- AUTO_INCREMENT для таблицы `Timetable`
--
ALTER TABLE `Timetable`
  MODIFY `TimeTableID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
