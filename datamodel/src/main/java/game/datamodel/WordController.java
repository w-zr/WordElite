package game.datamodel;

import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import game.datamodel.Model.Word;
import game.datamodel.Model.WordReporitory;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

@RestController
public class WordController {
    private final WordReporitory wordReporitory;

    public WordController(WordReporitory wordReporitory) {
        this.wordReporitory = wordReporitory;
    }

    @PostMapping("/word")
    String addWord(@RequestParam String word) {
        Word w = new Word(word);
        wordReporitory.save(w);
        return "New Word Saved.\n";
    }

    @GetMapping("/word/{difficulty}")
    List<String> getWordByDifficulty(@PathVariable Integer difficulty) {
        List<Word> words = wordReporitory.findAllByDifficulty(difficulty);
        List<String> re = new ArrayList<>();
        for (Word w : words) {
            re.add(w.getWord());
        }
        return re;
    }

    @GetMapping("/words")
    String getWord() {
        JsonObject object = new JsonObject();
        JsonArray jsonArray = new JsonParser().parse(new Gson().toJson(wordReporitory.findAll())).getAsJsonArray();
        object.add("words", jsonArray);

        return object.toString();
    }
}
