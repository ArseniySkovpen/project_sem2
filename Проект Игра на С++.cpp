#include <iostream>
#include <string>
#include <limits>
#include <vector>

class Item {
public:
    std::string name;
    int specific;

    Item(std::string name, int specific)
        : name(name), specific(specific) {}
};

class Weapon {
public:
    std::string name;
    int damage;

    Weapon(std::string n, int d) : name(n), damage(d) {}
};

class Player {
private:
    int health;
    std::vector<Item> inventory;
    Weapon* equippedWeapon;

public:
    Player(int hp) : health(hp), equippedWeapon(nullptr) {}

    void addItem(const Item& item) {
        if (inventory.size() < 5) {
            inventory.push_back(item);
            std::cout << "Вы получили предмет: " << item.name << "\n";
        }
        else {
            std::cout << "Инвентарь полон! Вы не можете взять больше предметов.\n";
        }
    }
    void showHP() const {
        std::cout << "Текущее здоровье игрока: " << health << "\n";
    }
    void showInventory() const {
        std::cout << "Предметы в инвентаре:\n";
        for (size_t i = 0; i < inventory.size(); ++i) {
            std::cout << i + 1 << ". " << inventory[i].name << " (восстановление: " << inventory[i].specific << " HP)\n";
        }
        if (inventory.empty()) {
            std::cout << "Инвентарь пуст.\n";
        }
    }
    void equipWeapon(Weapon* weapon) {
        equippedWeapon = weapon;
        std::cout << "Вы экипировали " << weapon->name << ". Урон: " << weapon->damage << "\n";
    }
    void takeDamage(int damage) {
        health -= damage;
        if (health <= 0) {
            health = 0;
            std::cout << "Вы погибли...\n";
        }
        else {
            std::cout << "Вы получили " << damage << " урона. Текущее здоровье: " << health << "\n";
        }
    }
};

void waitForKey() {
    std::cout << "Нажмите Enter для продолжения...\n";
    std::cin.get();
}
void waitForKeyEmpty() {
    std::cin.get();
}

class Game {
private:
    Player player{ 100 };
public:
    void start() {
        showIntro();
        firstChoice();
        firstDialogue();
        SecondChoice();
        ThirdChoice();
    }

private:
    void showIntro() {
        std::cout << "====================================================================================\n";
        std::cout << "\n Здравствуй! Сегодня ты погрузишься в удивительный мир, полный нечисти, боли и обид.\n";
        std::cout << "\n Верно! Вы попали в АД! Добро пожаловать в Visiting the devil!\n\n";
        std::cout << "====================================================================================\n";
        waitForKey();
    }

    void firstChoice() {
        std::cout << "Вы оказываетесь в странном месте...\n Вокруг темно и душно. Вы не понимаете, что произошло, потому что буквально пару секунд назад Вы переходили дорогу, идя в супермаркет.\n";
        std::cout << "Вы видите небольшое свечение вдалеке...\n";
        std::cout << "1. Идти на свет. \n";
        std::cout << "2. Остаться на месте\n";

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Очищаем ввод для следующего ввода

        switch (choice) {
        case 1:
            ComeLight();
            break;
        case 2:
            StayPut();
            break;
        default:
            std::cout << "Некорректный выбор. Пожалуйста, попытайтесь снова.\n";
            firstChoice(); // Повторный вызов выбора
            break;
        }
    }

    void ComeLight() {
        std::cout << "Вы идёте по какому-то коридору. Вокруг вас буквально ничего. Только страшный гул, который пробирает вас изнутри. Подойдя в плотную к свечению вы видите проход.\n";
        waitForKey();
        std::cout << "Пройдя сквозь свет вы видите множество людей в белых одеяниях, зелёные луга, деревья. Вы слышите знакомые имена...\n";
        std::cout << "Цезарь, Платон, Аристотель.... Где же вы оказались?\n";
        std::cout << "Чуть поодаль стоит странный мужчина, непохожий на остальных... Вы решаетесь подойти к нему.\n";
        waitForKey();
        firstDialogue();
    }

    void StayPut() {
        std::cout << "Резко свет пропадает за силуэтом странного человека...\n";
        std::cout << "Он идет к вам на встречу, хватает за руку и тащит вас к свету, несмотря на все ваши сопротивления.\n";
        std::cout << "Перед самим светом он пропадает и ничего не остаётся, кроме как войти в это свечение...\n";
        waitForKey();
        std::cout << "Пройдя сквозь свет вы видите множество людей в белых одеяниях, зелёные луга, деревья. Вы слышите знакомые имена...\n";
        std::cout << "Цезарь, Платон, Аристотель.... Где же вы оказались?\n";
        std::cout << "Чуть поодаль стоит странный мужчина, непохожий на остальных... Вы решаетесь подойти к нему.\n";
        waitForKey();
        firstDialogue();
    }

    void firstDialogue() {
        std::cout << "- Приветствую тебя! (Чтобы продолжать диалог нажимайте Enter) \n";
        waitForKeyEmpty();
        std::cout << "-Здравствуйте, а где это я?\n";
        waitForKeyEmpty();
        std::cout << "-Хах... Здравствуйте.... Здесь так не говорят, дорогой мой. Ты умер.\n";
        waitForKeyEmpty();
        std::cout << "-Что? Как это? Я же просто шёл в магазин!\n";
        waitForKeyEmpty();
        std::cout << "-Шёл и дорогу переходил, а по этой дороге ещё машина ехала, которая тебя и не заметила.\n";
        waitForKeyEmpty();
        std::cout << "-Вот как... Хорошо, хоть я в рай попал...\n";
        waitForKeyEmpty();
        std::cout << " - Рай ? С чего ты взял ? \n";
        waitForKeyEmpty();
        std::cout << "- Ну так... Всё зелёное, люди в белом, нет чертей.\n";
        waitForKeyEmpty();
        std::cout << "-Всё не так просто, как ты думаешь... Ты в Лимбе... Это Ад, правда только первый круг. И судя по твоему прошлому, ты здесь оказался не случайно.\n";
        waitForKeyEmpty();
        std::cout << "- А что не так с моим прошлым? \n";
        waitForKeyEmpty();
        std::cout << "-Так ты грешник, милок.\n Зная, сколько людей ты обманул на своём веку... Ты должен был оказаться на 8 кругу.\n Но раз ты здесь, то небеса дают тебе второй шанс. Чтобы ты смог пройти по всем кругам и помочь другим грешникам.\n Кому-то вознестись, кому-то помочь найти духовного спокойствия и многое другое.\n";
        waitForKeyEmpty();
        std::cout << "-Вот как... А почему именно я? \n";
        waitForKeyEmpty();
        std::cout << "-Не знаю. И не думаю, что кто-то другой знает. Только Сам Господь ведает.\n";
        waitForKeyEmpty();
        std::cout << "-И что мне делать сейчас?\n";
        waitForKeyEmpty();
        std::cout << "-Иди и найди Харона. Он хранитель первого круга, перевозчик душ...\n Если сможешь его к себе расположить и помочь грешнику, то он сможет направить тебя на второй круг.\n Увидимся на той стороне...\n";
        waitForKey();
        SecondChoice();
    }

    void SecondChoice() {
        std::cout << " Незнакомец исчез... Вы остались одни с осознанием того, что вы попали в Ад.\n ";
        std::cout << "Что Вы будете делать дальше?\n";
        std::cout << "1. Пройтись по округе \n";
        std::cout << "2. Поговорить с людьми в округе о Хароне \n";

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Очищаем ввод для следующего ввода

        switch (choice) {
        case 1:
            WalkAround();
            break;
        case 2:
            TalkPeople();
            break;
        default:
            std::cout << "Некорректный выбор. Пожалуйста, попытайтесь снова.\n";
            SecondChoice(); // Повторный вызов выбора
            break;
        }

    }

    void WalkAround() {
        std::cout << "Вы идёте вдоль зелёных лугов и не можете поверить, что это ад.\n";
        waitForKey();
        std::cout << "За одним из кустов вы замечаете поблёскивание...\n";
        std::cout << "Это оказывается бутылёк с красной жидкостью\n";
        std::cout << "На приклеенной на бутылек бумажке написано: Зелье лечения\n";
        waitForKey();
        std::cout << "Поздравляю! Вы нашли Зелье лечения. Эти небольшие флакончики порой могут спасти вам жизнь. Не забывайте, всегда носить с собой парочку.\n";
        std::cout << "Теперь вам доступен инвентарь! Помните, место ограничено! Подходите с умом к своему выбору!\n";
        // Добавляем зелье исцеления в инвентарь игрока
        player.addItem(Item("Зелье исцеления", 50));
        player.showInventory();
        waitForKey();
        std::cout << "Вы идетё дальше и замечаете протоптанную, словно табуном, тропинку.\n";
        waitForKey();
        std::cout << "- Хм... Если тут ходит так много людей, может там я и найду Харона\n";
        waitForKey();
        std::cout << "Идя по протоптанной тропинке, вы находите маленький,ржавый кинжал.\n";
        Weapon* dagger = new Weapon("Ржавый кинжал", 2); // Например, создаем кинжал
        player.equipWeapon(dagger); // Экипируем его  
        ThirdChoice();
    }

    void TalkPeople() {
        std::cout << "Вы подходите к людям, которые что-то обсуждают.\n";
        waitForKey();
        std::cout << "Один из них вас замечает.\n";
        waitForKey();
        std::cout << "-О, Новенький! С прибытием! Держи, угощайся!\n";
        waitForKey();
        std::cout << "Он даёт вам бутылёк с красной жидкостью\n";
        std::cout << "На приклеенной на бутылёк бумажке написано: Зелье лечения\n";
        // Добавляем зелье исцеления в инвентарь игрока
        player.addItem(Item("Зелье исцеления", 50));
        player.showInventory();
        waitForKey();
        std::cout << "- Большое спасибо за угощение! Вы не подскажите, где найти Харона? (Чтобы продолжать диалог нажимайте Enter)\n";
        waitForKeyEmpty();
        std::cout << "- Харона? Зачем он тебе?\n";
        waitForKeyEmpty();
        std::cout << "- Да я пока и сам не понимаю... Но судя по всему у меня есть миссия. И для ее выполнения мне нужен Харон. \n";
        waitForKeyEmpty();
        std::cout << "- Вот как. Ну раз так, то конечно подскажем. Иди вот по той тропинке к реке. Там ты увидишь пристань. Оттуда Харон перевозит души. \n";
        waitForKeyEmpty();
        std::cout << "- Большое спасибо \n";
        waitForKey();
        std::cout << "Идя по протоптанной тропинке, вы находите маленький,ржавый кинжал.\n";
        Weapon* dagger = new Weapon("Ржавый кинжал", 2); // Например, создаем кинжал
        player.equipWeapon(dagger); // Экипируем его
        ThirdChoice();
    }

    void ThirdChoice() {
        std::cout << "Вы выходите на берег реки. Там находится небольшая деревянная пристань и огромная очередь из людей.\n";
        std::cout << "Около пристани стоит небольшая лодка, на которой, держа весло стоит уродливый старик с растрёпанными волосами\n";
        std::cout << "Судя по всему это Харон...\n";
        waitForKey();
        std::cout << "1. Обойти очередь и подойти к старику.\n";
        std::cout << "2. Быть добросовестным и отстоять очередь.\n";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Очищаем ввод для следующего ввода

        switch (choice) {
        case 1:
            Pass();
            break;
        case 2:
            Standing();
            break;
        default:
            std::cout << "Некорректный выбор. Пожалуйста, попытайтесь снова.\n";
            firstChoice(); // Повторный вызов выбора
            break;
        }

       
    }
    void Standing() {
        std::cout << "Вы стоите в очереди очень долгое время.\n";
        waitForKey();
        std::cout << "Очень долгое время\n";
        waitForKey();
        std::cout << "ОЧЕНЬ ДОЛГОЕ ВРЕМЯ\n";
        waitForKey();
        std::cout << " Наконец до вас доходит очередь\n";
        waitForKey();
        std::cout << "- Вы Харон? (Чтобы продолжать диалог нажимайте Enter) \n";
        waitForKeyEmpty();
        std::cout << "- Я, я, кто ж ещё...(Он говорит так, будто бы прямо сейчас уснет стоя) \n";
        waitForKeyEmpty();
        std::cout << "- У меня немного странная просьба... \n";
        waitForKeyEmpty();
        std::cout << "- Хм... Неужели что-то интересное. Я слушаю\n";
        waitForKeyEmpty();
        std::cout << "- У меня есть своего рода миссия и для ёе выполнения мне нужно попасть на второй круг. Вы можете помочь мне в этом?\n";
        waitForKeyEmpty();
        std::cout << "- Неужели... Я таких как ты не видел уже несколько десятков веков, если не больше. Я помогу тебе, только если ты поможешь мне. \n";
        waitForKeyEmpty();
        std::cout << "- Да, конечно я готов! Что нужно делать? \n";
        waitForKeyEmpty();
        std::cout << "- Можешь подменить меня? Я работаю без отдыха уже столько времени, что не сосчитать. \n";
        waitForKeyEmpty();
        std::cout << "- Ну... Могу, а что нужно делать? \n";
        waitForKeyEmpty();
        std::cout << "- Ух, спасибо! Всё просто! Садишь этих в лодку, по одному, и плывешь на другой берег. Там садишь других и везешь сюда. Так раз 10 сделай. Я буду крайне благодарен и помогу тебе. \n";
        waitForKeyEmpty();
        std::cout << "- Хорошо! \n";
        waitForKey();
        std::cout << "Вы садитесь в лодку, загружаете людей и плывёте на другой берег, считая про себя...\n";
        waitForKey();
        std::cout << "- Раз \n";
        waitForKey();
        std::cout << "- Два \n";
        waitForKey();
        std::cout << "- Три... \n";
        waitForKey();
        std::cout << "И так до десяти... \n";
        waitForKey();
        std::cout << "Закончив своё испытание и вернувшись обратно, вы видите как Харон крепко спит под ближайшим деревом... \n";
        waitForKey();
        std::cout << "Вы его будите и сообщаете, что поручение выполнено. \n";
        waitForKey();
        std::cout << "- Спасибо тебе, избранник! Я как заново умер! Ха-ха-ха! Не обращай внимания, профессиональный юмор... \n";
        waitForKey();
        std::cout << "- Садись в лодку и поехали \n";
        waitForKey();


    }
    void Pass() {
        std::cout << "При попытке обойти очередь вас ловят за одежду двое мужчин и доходчиво объясняют, что так делать нельзя\n";
        player.takeDamage(10); // Игрок получает 10 урона
        waitForKey();
        Standing();
    }


};

int main() {
    setlocale(LC_ALL, "RU");
    Game game;
        game.start();
        return 0;
}
