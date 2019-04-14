package game.datamodel.Model;

import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;

public interface QuestionerRepository extends CrudRepository<Questioner, Integer> {
    List<Questioner> findAll();

    Optional<Questioner> findById(Integer id);

    @Query(value = "update Questioner set level=?1, numberOfQuestions=?2 where id=?3")
    @Modifying
    @Transactional
    void update(Integer level, Integer numberOfQuestions, Integer id);
}
