code Main

  -- OS Class: Project 3
  --
  -- <GAURAV KUNTE>
  --

-----------------------------  Main  ---------------------------------

  	function main ()
      	print ("SLEEPING BARBER AND GAMING PARLOR PROBLEMS\n")

      	InitializeScheduler ()

      	--SleepingBarber()
      	--GamingParlor()
        

    	ThreadFinish ()
  	endFunction



-------------------------SleepingBarber-------------------------------


  var
    chair: int 
    function_object: SB
    thArray: array [21] of Thread = new array of Thread {21 of new Thread }     --1 thread for the barber and 20 customer threads


  function SleepingBarber()

      function_object = new SB            -- creating a new object of class SB
      function_object.Init()
    


      print ("\n\n")

      thArray[0].Init ("Barber")
      thArray[1].Init ("Customers-1")
      thArray[2].Init ("Customers-2")
      thArray[3].Init ("Customers-3")
      thArray[4].Init ("Customers-4")
      thArray[5].Init ("Customers-5")
      thArray[6].Init ("Customers-6")
      thArray[7].Init ("Customers-7")
      thArray[8].Init ("Customers-8")
      thArray[9].Init ("Customers-9")
      thArray[10].Init ("Customers-10")
      thArray[11].Init ("Customers-11")
      thArray[12].Init ("Customers-12")
      thArray[13].Init ("Customers-13")
      thArray[14].Init ("Customers-14")
      thArray[15].Init ("Customers-15")
      thArray[16].Init ("Customers-16")
      thArray[17].Init ("Customers-17")
      thArray[18].Init ("Customers-18")
      thArray[19].Init ("Customers-19")
      thArray[20].Init ("Customers-20")

      


      thArray[0].Fork (fun1, 0)
      thArray[1].Fork (fun, 1)
      thArray[2].Fork (fun, 2)
      thArray[3].Fork (fun, 3)
      thArray[4].Fork (fun, 4)
      thArray[5].Fork (fun, 5)
      thArray[6].Fork (fun, 6)
      thArray[7].Fork (fun, 7)
      thArray[8].Fork (fun, 8)
      thArray[9].Fork (fun, 9)
      thArray[10].Fork (fun, 10)
      thArray[11].Fork (fun, 11)
      thArray[12].Fork (fun, 12)
      thArray[13].Fork (fun, 13)
      thArray[14].Fork (fun, 14)
      thArray[15].Fork (fun, 15)
      thArray[16].Fork (fun, 16)
      thArray[17].Fork (fun, 17)
      thArray[18].Fork (fun, 18)
      thArray[19].Fork (fun, 19) 
      thArray[20].Fork (fun, 20)

    ThreadFinish ()
  
  endFunction


  class SB
    superclass Object
    fields
      mlock: Mutex
      customers: Semaphore
      barber: Semaphore
      waiting: int
      

    methods
      Init()
      Barbers()
      Customers(id: int)
      get_haircut()
      cut_hair()
  endClass



  function fun1()

    -- Wrapper function for Barbers
    
    function_object.Barbers()
  


  endFunction

	
  function fun(id: int)

    -- Wrapper function for Customers 
    
    function_object.Customers(id)

  
  endFunction


  behavior SB

      method Init()
        mlock = new Mutex
        mlock.Init()
        customers = new Semaphore
        barber = new Semaphore 
        waiting = 0
        customers.Init(0)
        barber.Init(0)
        chair = 5

      endMethod

      method Barbers()
        
        while true
          customers.Down()    -- if there are no customers the barber goes to sleep 

          mlock.Lock()        -- when the first customer comes it wakes up the barber and the barber locks the lock
          
          waiting = waiting - 1   -- a customer from the waiting line takes a seat on the barbers chair  
          
          barber.Up()         -- barber is ready to cut  hair
          mlock.Unlock()
          function_object.cut_hair()    -- barber starts cutting the customers hair
        endWhile
      endMethod

      method Customers(id: int)

        var i: int

        for i = 0 to 500
          currentThread.Yield()     -- yielding to prevent all the customers from coming at the same time
        endFor

      
        mlock.Lock()

        print ("Number of chairs available = ")
        printInt(chair - waiting)
        print ("\t")
        

        if waiting < chair          -- if there are no empty chirs available in the shop, the customer leaves
          waiting = waiting + 1     -- if there are empty chairs, the customer gets in line
          print("\t\t\t\t\t\t\t\t\t\t\t\t")

          print (currentThread.name)
          print (" is seated\n\n")
          nl()
          customers.Up()            -- wake up barber if the barber is sleeping 
          mlock.Unlock()
          barber.Down()             -- barber goes to sleep if the number of customers become 0 

          function_object.get_haircut()

        else
          print ("The shop is full")
          print("\t\t\t\t\t\t\t\t\t\t") --the customer leaves the shop 
          print (currentThread.name)
          print (" is leaving\n\n")
          mlock.Unlock()

        endIf

      endMethod


      method get_haircut()

        var i: int
        print("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t")
        print(currentThread.name)
        print(" getting a haircut.\n\n")

        for i = 0 to 1000
          currentThread.Yield()   -- haircut takes some amount of time
        endFor

      endMethod

      method cut_hair()
        var i: int
        print("\t\t\t\t\t\t\t\t")
        print(currentThread.name)
        print(" cutting hair.\n\n")

        for i=1 to 1000
          currentThread.Yield()
        endFor

        print("\t\t\t\t\t\t\t\t")
        print(currentThread.name)
        print(" is done cutting hair.\n\n")
      endMethod





endBehavior





  




----------------------GamingParlor----------------------


  var 
    
    front_desk: GParlor
    players: array [8] of Thread = new array of Thread {8 of new Thread }   -- one thread for each group

  function GamingParlor ()

      front_desk = new GParlor
      front_desk.Init ()
      

      players[0].Init ("A")
      players[0].Fork (Desk, 4)

      players[1].Init ("B")
      players[1].Fork (Desk, 4)
      
      players[2].Init ("C")
      players[2].Fork (Desk, 5)

      players[3].Init ("D")
      players[3].Fork (Desk, 5)

      players[4].Init ("E")
      players[4].Fork (Desk, 2)

      players[5].Init ("F")
      players[5].Fork (Desk, 2)

      players[6].Init ("G")
      players[6].Fork (Desk, 1)

      players[7].Init ("H")
      players[7].Fork (Desk, 1)

      ThreadFinish()

     endFunction


  function Desk(dice: int)

  var i: int

  for i = 1 to 5

    front_desk.Request(dice)        -- the group requests the dice
    currentThread.Yield()           -- they take some time to play 
    front_desk.Return(dice)         -- the group returns the dice after playing
  
  endFor

  endFunction



class GParlor
    superclass Object
    fields
      game_lock: Mutex
      
      num_dice_available: int      -- total number of dice available in the parlor
      Group: int                  -- waiting line
      parlor_lobby: Condition    
    
    methods
      Init ()
      Request (dice: int)
      Return (dice: int)
      Print(str: String, count: int)
endClass

behavior GParlor

    method Init ()
      
      
      
      parlor_lobby  = new Condition
       
      parlor_lobby.Init()
      
      game_lock = new Mutex        
      game_lock.Init()
      
      num_dice_available = 8
      Group = 0

      
    endMethod

    method Request(dice: int)

      game_lock.Lock()

        front_desk.Print("requests", dice)

        Group = Group + 1

        if Group > 1                            -- to get at the head of the line
           parlor_lobby.Wait (& game_lock)
        endIf

        while dice > num_dice_available
          
          parlor_lobby.Wait( & game_lock)       -- number of dice needed to play that game are not available 
        

        endWhile

        num_dice_available = num_dice_available - dice    -- one group starts playing a particular game

        Group = Group - 1

        parlor_lobby.Signal( & game_lock)       -- waking another group and leaving

        front_desk.Print("proceeds with", dice)

      game_lock.Unlock()


    endMethod


    method Return(dice: int)

      game_lock.Lock()

        num_dice_available = num_dice_available + dice    -- return the dice after playing 

        front_desk.Print("releases and adds back", dice)
        
        
        parlor_lobby.Signal( & game_lock)     -- waking up the first group in line 
        
      game_lock.Unlock()


    endMethod


    method Print (str: String, count: int) --
-- This method prints the current threads name and the arguments. -- It also prints the current number of dice available.
        
        print (currentThread.name)
        print (" ")               
        print (str)
        print (" ")
        printInt (count)
        nl ()
        print ("------------------------------Number of dice now avail = ") printInt (num_dice_available)
        nl ()
    endMethod
    

  endBehavior





		
endCode
