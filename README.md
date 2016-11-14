# steganography

Моя попытка скрыть информацию в изображении.

Стегонография – сокрытие информации в любом мультимидийном источнике, чтобы оригинал крайне мало отличался от копии.

Все методы чтения реализованы в классе img. Ничего особенного, никаких новшеств.

У этого класса большая проблема – читает/записывает он только BMP форматы изображения, да и только 8-битного формата. Будьте осторожней, если вы вообще когда-нибудь его решитесь расширять.

А логика стегонографии описана в самом main.cpp файле. И там все просто – у каждого пикселя(8-бит) 1 бит заменяем нужной нашим битом, и так пока наши биты не кончатся, или биты у изображения, что, кстати, более вероятно.

Все.
