#include <sys/select.h>

#include "Socket.h"
#include "ClientData.h"

class Client {
	public:
  	// 
  	explicit Client (const char * ip, short port,
    		int timeout_sec, int timeout_usec);
  virtual ~Client() {};

		// true, если удалось отправить все данные.
		bool Send();

		// true, если удалось получить данные от сервера до таймаута.
    bool Recv();

		// true, если удалось корректно сообщить серверу о закрытии соединения.
		bool CloseConnection ();

		// true, если позиция машины была успешно изменена.
		bool SetPosition(const struct CarPosition * new_pos);

		// возвращает текущее положение машины.
		const struct CarPosition * GetPosition();

	protected:
		// true, если синхронизация с сервером прошла успешно.
    // в этой функции происходит инициализация начального положения машины.
		bool Synhronize();
  
  	// колличество отрисованных кадров.
	  long long int time_;

		// friend class Car;
	private:

		struct timeval timeout;

		Client (Client &orig);

		SockAddr * my_addr_;

    SockAddr * serv_addr_;

		UdpSock * my_sock_;

		ClientData * my_data_;
};
