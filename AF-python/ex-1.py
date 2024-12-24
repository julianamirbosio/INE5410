from time import sleep
from random import randint
from threading import Thread, Lock, Condition

def produtor():
  global buffer
  for i in range(10):
    sleep(randint(0,2))           # fica um tempo produzindo...
    item = 'item ' + str(i)
    with lock:
      while(len(buffer) == tam_buffer):
        print('>>> Buffer cheio. Produtor ira aguardar.')
        lugar_no_buffer.wait()    # aguarda que haja lugar no buffer
      buffer.append(item)
      print('Produzido %s (ha %i itens no buffer)' % (item,len(buffer)))
      item_no_buffer.notify()

def consumidor():
  global buffer
  for i in range(10):
    with lock:
      while(len(buffer) == 0):
        print('>>> Buffer vazio. Consumidor ira aguardar.')
        item_no_buffer.wait()   # aguarda que haja um item para consumir 
      item = buffer.pop(0)
      print('Consumido %s (ha %i itens no buffer)' % (item,len(buffer)))
      lugar_no_buffer.notify()
    sleep(randint(0,2))         # fica um tempo consumindo...

buffer = []
tam_buffer = 5
lock = Lock()
lugar_no_buffer = Condition(lock)
item_no_buffer = Condition(lock)
# produtor = Thread(target=produtor) 
# consumidor = Thread(target=consumidor) 

prod, cons = [], []

for i in range(2):
  prod.append(Thread(target=produtor))
  cons.append(Thread(target=consumidor))
  prod[i].start()
  cons[i].start()


for i in range(2):
  prod[i].join()
  cons[i].join()

# produtor.start()
# consumidor.start()
# produtor.join()
# consumidor.join() 