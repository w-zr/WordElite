package game.datamodel.Model;

import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;
import java.util.Optional;

public interface QuestionerRepository extends JpaRepository<Questioner, Integer> {
    List<Questioner> findAll();

    Optional<Questioner> findById(Integer id);
}
