package game.datamodel;

import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import game.datamodel.DAO.PlayerDAO;
import game.datamodel.DAO.QuestionerDAO;
import game.datamodel.Model.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.LinkedList;
import java.util.List;
import java.util.Optional;

@RestController
public class Controller {
    private final UserRepository userRepository;
    private final PlayerRepository playerRepository;
    private final QuestionerRepository questionerRepository;

    @Autowired
    public Controller(UserRepository userRepository, PlayerRepository playerRepository,
                      QuestionerRepository questionerRepository) {
        this.userRepository = userRepository;
        this.playerRepository = playerRepository;
        this.questionerRepository = questionerRepository;
    }

    @PostMapping("/users")
    String addUser(@RequestParam String username, @RequestParam String password) {
        User u = new User(username, password);
        Player p = new Player(0, 0, 0, u);
        Questioner q = new Questioner(0, 0, u);

        userRepository.save(u);
        playerRepository.save(p);
        questionerRepository.save(q);

        return "New user saved\n";
    }

    @GetMapping("/users")
    String findAllUsers() {
        JsonObject object = new JsonObject();
        JsonArray jsonArray = new JsonParser().parse(new Gson().toJson(userRepository.findAll())).getAsJsonArray();
        object.add("users", jsonArray);

        return object.toString();
    }

    @GetMapping("/players")
    String findAllPlayers() {
        JsonObject object = new JsonObject();
        List<Player> players = playerRepository.findAll();
        List<PlayerDAO> playerDAOS = new LinkedList<>();
        for (Player p : players) {
            PlayerDAO pd = new PlayerDAO(p);
            playerDAOS.add(pd);
        }
        JsonArray jsonArray = new JsonParser().parse(new Gson().toJson(playerDAOS)).getAsJsonArray();
        object.add("players", jsonArray);
        return object.toString();
    }

    @GetMapping("/questioners")
    String findAllQuestioners() {
        JsonObject object = new JsonObject();
        List<Questioner> questioners = questionerRepository.findAll();
        List<QuestionerDAO> questionerDAOS = new LinkedList<>();
        for (Questioner q : questioners) {
            QuestionerDAO qd = new QuestionerDAO(q);
            questionerDAOS.add(qd);
        }
        JsonArray jsonArray = new JsonParser().parse(new Gson().toJson(questionerDAOS)).getAsJsonArray();
        object.add("questioners", jsonArray);
        return object.toString();
    }

    @PutMapping("/players/{id}")
    String updataPlayer(@PathVariable Integer id, @RequestParam Integer exp, @RequestParam Integer level, @RequestParam Integer totalPassedStage) {
        Optional<Player> p = playerRepository.findById(id);
        if (p.isEmpty()) {
            return "Player " + id + " is not in the database.\n";
        }
        p.get().setExp(exp);
        p.get().setLevel(level);
        p.get().setTotalPassedStage(totalPassedStage);
        playerRepository.save(p.get());
        return "Player " + id + " is updated.\n";
    }

    @PutMapping("/questioners/{id}")
    String updateQuestioner(@PathVariable Integer id, @RequestParam Integer level, @RequestParam Integer numberOfQuestions) {
        Optional<Questioner> q = questionerRepository.findById(id);
        if (q.isEmpty()) {
            return "Questioner " + id + " is not in the database.\n";
        }
        q.get().setLevel(level);
        q.get().setNumberOfQuestions(numberOfQuestions);
        questionerRepository.save(q.get());
        return "Questioner " + id + " is updated\n";
    }
}