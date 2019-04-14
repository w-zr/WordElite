package game.datamodel.Model;

import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface WordReporitory extends CrudRepository<Word, Integer> {
    List<Word> findAllByDifficulty(Integer difficulty);
}
