<title> Регистрация | Perfect World</title>
<head>
<meta http-equiv="content-type" content="text/html"; charset="UTF-8" />
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<center>
<form id="register" action="?do=register" method=post>
	<br><h3> Регистрация на сервере </h3><br>
	<br><h3> Рerfect World Server php 7.+ by Virtus </h3><br>
<center>
Логин:<br>
<input class="input_box" type=text name=login><br>
Пароль:<br>
<input class="input_box" type=password name=passwd><br>
Повтор пароля:<br>
<input class="input_box" type=password name=repasswd><br>
E-Mail:<br>
<input class="input_box" type=text name=email><br>
<input class="input_submit" type=submit name=submit value="Регистрация"><br>
</table>
</form>

<?php
//Powered by Virtus

$config = array
(
		'host'	=>	'localhost',				// Хост
		'user'	=>	'root',						// Имя пользователя
		'pass'	=>	'3444',			// Пароль от БД
		'name'	=>	'pw',						// Название БД
		'gold'	=>	'1000000000',				// Количество голда
);

    if (isset($_POST['login']))
        {
			$link = mysqli_connect($config['host'], $config['user'], $config['pass']) or die ("Нет соединения с MySQL");
			mysqli_select_db($link, $config['name']) or die ("Базы ".$DBName." не существует.");
            
            $Login = $_POST['login'];
            $Pass = $_POST['passwd'];
            $Repass = $_POST['repasswd'];
            $Email = $_POST['email'];
            
            $Login = StrToLower(Trim($Login));
            $Pass = StrToLower(Trim($Pass));
            $Repass = StrToLower(Trim($Repass));
            $Email = Trim($Email);

        if (empty($Login) || empty($Pass) || empty($Repass) || empty($Email))
            {
                echo "Все поля заполнены не верно!";
            }
            
        elseif (StrPos('\'', $Email))
            {
                echo "Не верный формат E-Mail";
            }
            
        elseif ((StrLen($Login) < 4) or (StrLen($Login) > 10))
            {
                echo "Логин должен содержать не менее 4 и не более 10 смволов.";
            }
                    else
            {
                $Result = mysqli_query($link, "SELECT name FROM users WHERE name='$Login'") or ("Can't execute query.");
                
        if (mysqli_num_rows($Result))
            {
                echo "<font color='red'>Логин</font> <b>".$Login."</b> <font color='red'>уже есть в базе -_-</font>";
            }
            
        elseif ((StrLen($Pass) < 4) or (StrLen($Pass) > 10))
            {
                echo "Пароль должен содержать не менее 4 и не более 10 смволов.";
            }
            
        elseif ((StrLen($Repass) < 4) or (StrLen($Repass) > 10))
            {
                echo "Повтор пароля должен содержать не менее 4 и не более 10 смволов";
            }
            
        elseif ((StrLen($Email) < 4) or (StrLen($Email) > 25))
            {
                echo "E-Mail  должен содержать не менее 4 и не более 25 смволов";
            }
		else
			{
				$Result = mysqli_query($link, "SELECT name FROM users WHERE name='$Email'") or ("Can't execute query.");
		if (mysqli_num_rows($Result))
			{
				echo "<font color='red'>E-Mail</font> <b>".$Email."</b> <font color='red'>уже есть в базе.</font>";
			}
            
        elseif ($Pass != $Repass)
            {
                echo "Пароли не совпадают";
            }        
        else
            {
            	//$Salt = $Login.$Pass;
				//$Salt = md5($Salt);
                //$Salt = "0x".$Salt;
				$Salt = base64_encode(md5($Login.$Pass, true));
				mysqli_query($link, "call adduser('$Login', '$Salt', '0', '0', '0', '0', '$Email', '0', '0', '0', '0', '0', '0', '0', '', '', '$Salt')") or die ("Аккаунт не зарегистрирован");
				$mysqlres = mysqli_query($link, "select * from `users` WHERE `name`='$Login'");
				$User_ID = mysqli_fetch_array($mysqlres);
				mysqli_query($link, "call usecash({$User_ID['ID']},1,0,1,0,".$config['gold'].",1,@error)") or die ("Голд не выдан");
			echo "<font color='green'>Аккаунт <b>".$Login."</b> Успешно зарегистрирован :) Ваш ID: ".$User_ID['ID']." <br/> ".$config['gold']." голда начислено. Голд придет в течении 5-10 минут";
				}
			}
		}
	}
 echo $Data;
?>